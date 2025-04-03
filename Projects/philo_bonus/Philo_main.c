#include "Philo_header.h"

size_t	ft_get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_usleep(size_t time_to_sleep)
{
	size_t	start_time;

	start_time = ft_get_current_time();
	while (ft_get_current_time() - start_time < time_to_sleep)
		usleep(100);
}

void	ft_cleanup(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->i)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->monitor);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/monitor");
	ft_exit(0);
}

void	ft_create_processes(t_data *data)
{
	while (data->i < data->num_philos)
	{
		data->philos[data->i].pid = fork();
		if (data->philos[data->i].pid == -1)
		{
			ft_print_usage_and_exit("failed fork.");
			ft_exit(-1);
		}
		if (data->philos[data->i].pid == 0)
		{
			if (data->num_philos == 1)
			{
				ft_philo_one(&data->philos[data->i]);
				ft_exit(0);
			}
			else
			{
				ft_philosopher_routine(&data->philos[data->i]);
				ft_exit(0);
			}
		}
		data->i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		ft_print_usage_and_exit(NULL);
	ft_philo_pars(&data, ac, av);
	ft_philo_init(&data);
	sem_wait(data.monitor);
	ft_create_processes(&data);
	sem_wait(data.monitor);
	ft_cleanup(&data);
	return (0);
}
