/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:43:34 by souaammo          #+#    #+#             */
/*   Updated: 2025/04/03 15:43:36 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_header.h"

void	ft_philo_one(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, ft_print_status_one_philo, philo);
	pthread_join(thread, NULL);
}

void	ft_philo_create(t_data *data)
{
	short	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, ft_philosopher_routine,
			&data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor_threads, NULL, ft_monitor_threads, data);
}

void	ft_philo_wait(t_data *data)
{
	short	i;

	i = 0;
	pthread_join(data->monitor_threads, NULL);
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	ft_philo_destroy(t_data *data)
{
	short	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(data->philos[i].print_mutex);
		i++;
	}
	ft_exit(0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		ft_print_usage_and_exit(NULL);
	ft_philo_pars(&data, ac, av);
	ft_philo_init(&data, -1);
	if (data.num_philos == 1)
		ft_philo_one(&data.philos[0]);
	else
	{
		ft_philo_create(&data);
		ft_philo_wait(&data);
	}
	ft_philo_destroy(&data);
	return (0);
}
