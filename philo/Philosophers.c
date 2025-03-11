#include "Philosophers.h"

void ft_print_usage_and_exit(void)
{
    printf("Error: The program requires 4 or 5 arguments.\n");
    printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat ");
    printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
    printf("Note: All arguments must be positive integers between 1 and 2147483647.\n");
    ft_exit(EXIT_FAILURE);
}

void ft_print_and_exit(const char *msg)
{
    printf("Error: %s\n", msg);
    ft_exit(EXIT_FAILURE);
}

int ft_atoi(const char *str)
{
    size_t i = 0;
    long res = 0;
    
    if (!str || !str[0])
        ft_print_and_exit("All arguments must be positive integers.");
    
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
        return (-1);
    
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        res = res * 10 + (str[i] - '0');
        if (res > 2147483647)
            return (-1);
        i++;
    }
    if (str[i] != '\0')
        ft_print_and_exit("All arguments must be positive integers.");
    
    return ((int)res);
}

void ft_parse_philo(int ac, char **av, t_philo *philos)
{
    (void)ac;
    philos->num_philos = ft_atoi(av[1]);
    if (philos->num_philos <= 0)
        ft_print_and_exit("number_of_philosophers must be greater than 0.");
    philos->time_to_die = ft_atoi(av[2]);
    if (philos->time_to_die <= 0)
        ft_print_and_exit("time_to_die must be greater than 0.");
    philos->time_to_eat = ft_atoi(av[3]);
    if (philos->time_to_eat <= 0)
        ft_print_and_exit("time_to_eat must be greater than 0.");
    philos->time_to_sleep = ft_atoi(av[4]);
    if (philos->time_to_sleep <= 0)
        ft_print_and_exit("time_to_sleep must be greater than 0.");
    if (av[5])
    {
        philos->num_times_to_eat = ft_atoi(av[5]);
        if (philos->num_times_to_eat < 0)
            ft_print_and_exit("number_of_times_each_philosopher_must_eat must be >= 0.");
    }
    else
        philos->num_times_to_eat = -1;
}

long ft_get_current_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_usleep(long time_in_ms)
{
    long start_time = ft_get_current_time();
    while (ft_get_current_time() - start_time < time_in_ms)
        usleep(100);
}

void ft_philo_init(t_data *data)
{
    long i = 0;
    
    while (i < data->num_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}

void ft_philo_destroy(t_data *data)
{
    long i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(data->philos[i].print_mutex);
        i++;
    }
    ft_exit(0);
}

void ft_print_philo(t_philo *philo, char *msg)
{
    long current_time;

    current_time = ft_get_current_time();
    pthread_mutex_lock(philo->print_mutex);
    printf("%ld\t%ld\t%s\n", current_time, philo->id_philo, msg);
    pthread_mutex_unlock(philo->print_mutex);
}

void *ft_philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        if (philo->num_times_to_eat == 0)
            break;

        if (philo->id_philo % 2 == 0)
        {
            pthread_mutex_lock(philo->right_fork);
            ft_print_philo(philo, "has taken a fork");

            pthread_mutex_lock(philo->left_fork);
            ft_print_philo(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            ft_print_philo(philo, "has taken a fork");

            pthread_mutex_lock(philo->right_fork);
            ft_print_philo(philo, "has taken a fork");
        }

        ft_print_philo(philo, "is eating");
        philo->last_meal_time = ft_get_current_time();
        ft_usleep(philo->time_to_eat);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        if (philo->num_times_to_eat > 0)
            philo->num_times_to_eat--;

        if (ft_get_current_time() - philo->last_meal_time > philo->time_to_die)
        {
            ft_print_philo(philo, "died");
            ft_exit(0);
        }

        ft_print_philo(philo, "is sleeping");
        ft_usleep(philo->time_to_sleep);

        ft_print_philo(philo, "is thinking");
    }
    ft_exit(0);
    return (0);
}


void *ft_monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    long i;

    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(data->philos[i].print_mutex);
            if (ft_get_current_time() - data->philos[i].last_meal_time > data->philos[i].time_to_die)
            {
                printf("%ld %ld died\n", ft_get_current_time(), data->philos[i].id_philo);
                pthread_mutex_unlock(data->philos[i].print_mutex);
                ft_exit(0);
            }
            pthread_mutex_unlock(data->philos[i].print_mutex);
            i++;
        }
        usleep(500);
    }
    return NULL;
}


int main(int ac, char **av)
{
    t_data data;
    long i;

    if (ac < 5 || ac > 6)
        ft_print_usage_and_exit();
    data.num_philos = ft_atoi(av[1]);
    if (data.num_philos < 1)
        ft_print_and_exit("There must be at least 1 philosopher.");
    data.forks = ft_malloc(sizeof(pthread_mutex_t) * data.num_philos);
    data.philos = ft_malloc(sizeof(t_philo) * data.num_philos);
    if (!data.forks || !data.philos)
        ft_print_and_exit("Memory allocation failed.");
    ft_philo_init(&data);
    i = 0;
    while (i < data.num_philos)
    {
        data.philos[i].id_philo = i + 1;
        ft_parse_philo(ac, av, &data.philos[i]);
        data.philos[i].left_fork = &data.forks[i];
        data.philos[i].right_fork = &data.forks[(i + 1) % data.num_philos];
        data.philos[i].last_meal_time = ft_get_current_time();
        data.philos[i].print_mutex = ft_malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(data.philos[i].print_mutex, NULL);
        data.philos[i].data = &data;
        i++;
    }
    i = 0;
    while (i < data.num_philos)
    {
        pthread_create(&data.philos[i].thread, NULL, ft_philosopher_routine, &data.philos[i]);
        i++;
    }
    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, ft_monitor, &data);
    pthread_join(monitor_thread, NULL);
    
    i = 0;
    while (i < data.num_philos)
    {
        pthread_join(data.philos[i].thread, NULL);
        i++;
    }

    ft_philo_destroy(&data);
    ft_exit(0);
    return 0;
}

