#include "Philo.h"

void ft_print_usage_and_exit(char *msg)
{
    if (!msg)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat ");
        printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        printf("Note: All arguments must be positive integers between 1 and 2147483647.\n");
        printf("Error: The program requires 4 or 5 arguments.\n");
    }
    else
        printf("Error: %s\n", msg);
    ft_exit(EXIT_FAILURE);
}

int ft_atoi(const char *str)
{
    short   i;
    size_t  res;
    
    i = 0;
    res = 0;
    if (!str || !str[0])
        ft_print_usage_and_exit("All arguments must be positive integers.");
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
        ft_print_usage_and_exit("All arguments must be positive integers.");
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        res = res * 10 + (str[i] - '0');
        if (res > 2147483647)
            ft_print_usage_and_exit("All arguments must be positive integers.");
        i++;
    }
    if (str[i] != '\0')
        ft_print_usage_and_exit("All arguments must be positive integers.");
    return ((int)res);
}

void    ft_philo_pars(t_data *data, int ac, char **av)
{
    if (!data || !ac || !av)
        ft_print_usage_and_exit("ft_philo_pars arguments.");
    data->num_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->num_to_eat = ft_atoi(av[5]);
    else
        data->num_to_eat = -1;
    if (data->num_philos < 1 || data->num_philos > 200)
        ft_print_usage_and_exit("Number of philosophers must be between 1 and 200.");
    if (data->time_to_die < 60) 
        ft_print_usage_and_exit("time_to_die must be at least 60 ms.");
    if (data->time_to_eat < 60) 
        ft_print_usage_and_exit("time_to_eat must be at least 60 ms.");
    if (data->time_to_sleep < 60)
        ft_print_usage_and_exit("time_to_sleep must be at least 60 ms.");
    if (data->num_to_eat == 0)
        ft_exit(0);
}

size_t ft_get_current_time(void)
{
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void    ft_philo_init(t_data *data)
{
    short   i;

    if (!data)
        ft_print_usage_and_exit("ft_philo_init arguments.");
    data->forks = ft_malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = ft_malloc(sizeof(t_philo) * data->num_philos);
    data->time_start_program = ft_get_current_time();
    data->is_died = 0;
    i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id_philo = i + 1;
        data->philos[i].time_to_die = data->time_to_die;
        data->philos[i].time_to_eat = data->time_to_eat;
        data->philos[i].time_to_sleep = data->time_to_sleep;
        data->philos[i].num_to_eat = data->num_to_eat;
        pthread_mutex_init(&data->forks[i], NULL);
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].print_mutex = ft_malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(data->philos[i].print_mutex, NULL);
        data->philos[i].last_meal_time = ft_get_current_time();
        data->philos[i].data = data;
        i++;
    }    
}
