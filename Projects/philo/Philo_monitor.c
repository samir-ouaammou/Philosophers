/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:41:35 by souaammo          #+#    #+#             */
/*   Updated: 2025/04/04 14:41:38 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_header.h"

void	*ft_monitor_threads(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->j = -1;
	pthread_mutex_lock(&data->died_mutex);
	while (!data->is_died)
	{
		if (++data->j == 0)
			pthread_mutex_unlock(&data->died_mutex);
		data->i = -1;
		while (++data->i < data->num_philos)
		{
			pthread_mutex_lock(data->philos[data->i].print_mutex);
			pthread_mutex_lock(&data->last_meal);
			if (ft_remainder_of_monitor_func1(data))
				return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

int	ft_remainder_of_monitor_func1(t_data *data)
{
	if (ft_get_current_time() - data->philos[data->i].last_meal_time
		> data->philos[data->i].time_to_die)
	{
		pthread_mutex_unlock(&data->last_meal);
		pthread_mutex_lock(&data->died_mutex);
		if (data->is_died)
		{
			pthread_mutex_unlock(&data->died_mutex);
			pthread_mutex_unlock (data->philos[data->i].print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->died_mutex);
		return ((ft_remainder_of_monitor_func2(data, data->i)), (1));
	}
	pthread_mutex_unlock(&data->last_meal);
	pthread_mutex_unlock(data->philos[data->i].print_mutex);
	return (0);
}

void	ft_remainder_of_monitor_func2(t_data *data, short i)
{
	pthread_mutex_lock(&data->died_mutex);
	data->is_print = 1;
	pthread_mutex_unlock(&data->died_mutex);
	usleep(500);
	printf("%ld\t%d\tdied\n", ft_get_current_time() - data->time_start_program,
		data->philos[i].id_philo);
	pthread_mutex_unlock(data->philos[i].print_mutex);
	pthread_mutex_lock(&data->died_mutex);
	data->is_died = 1;
	pthread_mutex_unlock(&data->died_mutex);
}
