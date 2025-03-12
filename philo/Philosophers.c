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

void ft_philo_init(t_data *data, char **av)
{
    ssize_t i = 0;
    
    while (i < data->num_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        data->philos[i].id_philo = i + 1;
        ft_parse_philo(av, &data->philos[i]);
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].last_meal_time = ft_get_current_time();
        data->philos[i].print_mutex = ft_malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(data->philos[i].print_mutex, NULL);
        data->philos[i].data = data;
        i++;
    }
}

void ft_philo_destroy(t_data *data)
{
    ssize_t i = 0;
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
    ssize_t current_time;

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
            ft_exit(0);

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
    t_data *data;
    ssize_t i;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(data->philos[i].print_mutex);
            if (ft_get_current_time() - data->philos[i].last_meal_time > data->philos[i].time_to_die)
            {
                printf("%ld\t%ld\tdied\n", ft_get_current_time(), data->philos[i].id_philo);
                pthread_mutex_unlock(data->philos[i].print_mutex);
                ft_exit(0);
            }
            pthread_mutex_unlock(data->philos[i].print_mutex);
            i++;
        }
        usleep(500);
    }
    ft_exit(0);
    return NULL;
}


int main(int ac, char **av)
{
    t_data data;
    ssize_t i;

    if (ac < 5 || ac > 6)
        ft_print_usage_and_exit();
    data.num_philos = ft_atoi(av[1]);
    if (data.num_philos < 1)
        ft_print_and_exit("There must be at least 1 philosopher.");
    data.forks = ft_malloc(sizeof(pthread_mutex_t) * data.num_philos);
    data.philos = ft_malloc(sizeof(t_philo) * data.num_philos);
    if (!data.forks || !data.philos)
        ft_print_and_exit("Memory allocation failed.");
    ft_philo_init(&data, av);
    
    i = 0;
    while (i < data.num_philos)
    {
        pthread_create(&data.philos[i].thread, NULL, ft_philosopher_routine, &data.philos[i]);
        i++;
    }
    pthread_create(&data.monitor_thread, NULL, ft_monitor, &data);
    pthread_join(data.monitor_thread, NULL);
    
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

