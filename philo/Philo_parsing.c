#include "Philosophers.h"

int ft_atoi(const char *str)
{
    ssize_t i = 0;
    ssize_t res = 0;
    
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

void ft_parse_philo(char **av, t_philo *philos)
{
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
