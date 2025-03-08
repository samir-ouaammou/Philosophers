#include "Philosophers.h"

void	ft_print_usage_and_exit(void)
{
	printf("\nError: The program requires 4 or 5 arguments.\n");
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	printf("Note: All arguments must be positive integers between 1 and 2147483647.\n\n");
	ft_exit(-1);
}

int	ft_atoi(char *str)
{
	size_t	i;
	long	res;

	if (!str || !str[0])
		ft_print_usage_and_exit();
	i = 0;
	res = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			ft_print_usage_and_exit();
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
			ft_print_usage_and_exit();
		i++;
	}
	if (str[i])
		ft_print_usage_and_exit();
	return (res);
}

void	ft_parse_philo(int ac, char **av, t_philo_config *args)
{
	args->num_philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->num_times_to_eat = ft_atoi(av[5]);
	if (args->num_philosophers <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		ft_print_usage_and_exit();
}
