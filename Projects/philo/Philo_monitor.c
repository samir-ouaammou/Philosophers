/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_routine_utels.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:44:03 by souaammo          #+#    #+#             */
/*   Updated: 2025/04/03 15:44:05 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_header.h"

void	ft_remainder_of_func_ft_monitor_threads(t_data *data, short i)
{
	data->is_print = 1;
	usleep(500);
	printf("%ld\t%d\tdied\n", ft_get_current_time() - data->time_start_program,
		data->philos[i].id_philo);
	pthread_mutex_unlock(data->philos[i].print_mutex);
	data->is_died = 1;
}
void	*ft_monitor_threads(void *arg)
{
	t_data	*data;
	short	i;

	data = (t_data *)arg;
	while (!data->is_died)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			pthread_mutex_lock(data->philos[i].print_mutex);
			if (ft_get_current_time()
				- data->philos[i].last_meal_time > data->philos[i].time_to_die)
			{
				if (data->is_died)
					return ((pthread_mutex_unlock(data->philos[i].print_mutex)),
						(NULL));
				ft_remainder_of_func_ft_monitor_threads(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(data->philos[i].print_mutex);
		}
		usleep(500);
	}
	return (NULL);
}
