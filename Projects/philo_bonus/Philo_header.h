/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:49:04 by souaammo          #+#    #+#             */
/*   Updated: 2025/04/03 15:49:06 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include "malloc/malloc.h"
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pid_t				pid;
	size_t				id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	ssize_t				num_to_eat;
	size_t				last_meal;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	size_t				i;
	size_t				num_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	ssize_t				num_to_eat;
	size_t				start_time;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*monitor;
	t_philo				*philos;
}						t_data;

int						ft_atoi(const char *str);
size_t					ft_get_current_time(void);
void					ft_philo_init(t_data *data);
void					ft_philo_one(t_philo *philo);
void					ft_usleep(size_t time_to_sleep);
void					ft_print_usage_and_exit(char *msg);
int						ft_philosopher_routine(t_philo *philo);
void					ft_print_status(t_philo *philo, char *status);
void					ft_philo_pars(t_data *data, int ac, char **av);

#endif
