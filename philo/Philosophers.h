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
    long            id_philo;
    long            num_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            num_times_to_eat;
    long            last_meal_time;
    long            times_eaten;
    t_data          *data;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print_mutex;
} t_philo;

typedef struct s_data
{
    long            num_philos;
    t_philo         *philos;
    pthread_mutex_t *forks;
} t_data;



#endif
