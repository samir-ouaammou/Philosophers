#ifndef PHILOSOPHOERS_H
#define PHILOSOPHOERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "malloc/malloc.h"

typedef struct s_data t_data;

typedef struct s_philo
{
    ssize_t            id_philo;
    ssize_t            num_philos;
    ssize_t            time_to_die;
    ssize_t            time_to_eat;
    ssize_t            time_to_sleep;
    ssize_t            num_times_to_eat;
    ssize_t            last_meal_time;
    ssize_t            times_eaten;
    t_data          *data;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print_mutex;
} t_philo;

typedef struct s_data
{
    ssize_t            num_philos;
    t_philo         *philos;
    pthread_t       monitor_thread;
    pthread_mutex_t *forks;
} t_data;

void ft_parse_philo(char **av, t_philo *philos);
int ft_atoi(const char *str);
void ft_usleep(ssize_t time_in_ms);
ssize_t ft_get_current_time(void);
void ft_print_and_exit(const char *msg);

#endif
