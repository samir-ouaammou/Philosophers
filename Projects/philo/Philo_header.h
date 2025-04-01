#ifndef PHILO_HEADER_H
#define PHILO_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "malloc/malloc.h"

typedef struct s_data t_data;

typedef struct s_philo
{
    short           id_philo;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    ssize_t         num_to_eat;
    size_t          last_meal_time;
    t_data          *data;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print_mutex;
} t_philo;

typedef struct s_data
{
    short           is_died;
    short           num_philos;
    size_t          time_start_program;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    size_t          num_to_eat;
    t_philo         *philos;
    pthread_t       monitor_threads;
    pthread_mutex_t *forks;
} t_data;

size_t              ft_get_current_time(void);
void                ft_philo_init(t_data *data);
void                *ft_monitor_threads(void *arg);
void                ft_usleep(size_t time_to_sleep);
void                *ft_philosopher_routine(void *arg);
void                ft_print_usage_and_exit(char *msg);
void                ft_print_status(t_philo *philo, char *msg);
void                ft_philo_pars(t_data *data, int ac, char **av);
#endif
