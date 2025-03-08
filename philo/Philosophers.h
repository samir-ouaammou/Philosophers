#ifndef PHILOSOPHOERS_H
#define PHILOSOPHOERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "malloc/malloc.h"

typedef struct s_philo_config
{
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_to_eat;
} t_philo_config;


#endif