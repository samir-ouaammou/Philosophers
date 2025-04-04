/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:43:55 by souaammo          #+#    #+#             */
/*   Updated: 2025/04/03 15:43:56 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_header.h"

void	ft_usleep(size_t time_to_sleep)
{
	size_t	current_time;

	current_time = ft_get_current_time();
	while (ft_get_current_time() - current_time < time_to_sleep)
		usleep(100);
}

void	ft_print_status(t_philo *philo, char *msg)
{
	size_t	current_time;

	if (philo->data->is_died || philo->data->is_print)
		return ;
	current_time = ft_get_current_time();
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld\t%d\t%s\n", current_time - philo->data->time_start_program,
		philo->id_philo, msg);
	pthread_mutex_unlock(philo->print_mutex);
}

void	ft_lock_fork(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		usleep(200);
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
	}
}

void	*ft_philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->is_died)
	{
		if (philo->num_to_eat == 0)
			return ((philo->data->is_died = 1), (NULL));
		ft_lock_fork(philo);
		ft_print_status(philo, "is eating");
		philo->last_meal_time = ft_get_current_time();
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (philo->num_to_eat > 0)
			philo->num_to_eat--;
		if (ft_get_current_time() - philo->last_meal_time > philo->time_to_die)
			return (usleep(100), (ft_print_status(philo, "died")), (NULL));
		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		ft_print_status(philo, "is thinking");
	}
	return (0);
}
