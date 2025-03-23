#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <semaphore.h>
#include "malloc/malloc.h"

typedef struct s_data t_data;

typedef struct s_philo
{
    pid_t           pid;
    ssize_t         id;
    ssize_t         time_to_die;
    ssize_t         time_to_eat;
    ssize_t         time_to_sleep;
    ssize_t         num_to_eat;
    ssize_t         last_meal;
    t_data          *data;
} t_philo;

typedef struct s_data
{
    ssize_t         i;
    ssize_t         num_philos;
    ssize_t         time_to_die;
    ssize_t         time_to_eat;
    ssize_t         time_to_sleep;
    ssize_t         num_to_eat;
    ssize_t         start_time;
    sem_t           *forks;
    sem_t           *print;
    sem_t           *monitor;
    t_philo         *philos;
} t_data;

void ft_print_usage_and_exit(char *msg)
{
    if (!msg)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat ");
        printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        printf("Note: All arguments must be positive integers between 1 and 2147483647.\n");
        printf("Error: The program requires 4 or 5 arguments.\n");
    }
    else
        printf("Error: %s\n", msg);
    ft_exit(EXIT_FAILURE);
}

int ft_atoi(const char *str)
{
    short   i;
    ssize_t  res;
    
    i = 0;
    res = 0;
    if (!str || !str[0])
        ft_print_usage_and_exit("All arguments must be positive integers.");
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
        ft_print_usage_and_exit("All arguments must be positive integers.");
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        res = res * 10 + (str[i] - '0');
        if (res > 2147483647)
            ft_print_usage_and_exit("All arguments must be positive integers.");
        i++;
    }
    if (str[i] != '\0')
        ft_print_usage_and_exit("All arguments must be positive integers.");
    return ((int)res);
}

void    ft_philo_pars(t_data *data, int ac, char **av)
{
    if (!data || !ac || !av)
        ft_print_usage_and_exit("ft_philo_pars arguments.");
    data->num_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->num_to_eat = ft_atoi(av[5]);
    else
        data->num_to_eat = -1;
    if (data->num_philos < 1 || data->num_philos > 200)
        ft_print_usage_and_exit("Number of philosophers must be between 1 and 200.");
    if (data->time_to_die < 60) 
        ft_print_usage_and_exit("time_to_die must be at least 60 ms.");
    if (data->time_to_eat < 60) 
        ft_print_usage_and_exit("time_to_eat must be at least 60 ms.");
    if (data->time_to_sleep < 60)
        ft_print_usage_and_exit("time_to_sleep must be at least 60 ms.");
    if (data->num_to_eat == 0)
        ft_exit(0);
}

void    ft_cleanup(t_data *data)
{
    short   i;

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

ssize_t ft_get_current_time(void)
{
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void    ft_philo_init(t_data *data)
{
    short   i;

    data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philos);
    data->print = sem_open("/print", O_CREAT, 0644, 1);
    data->monitor = sem_open("/monitor", O_CREAT, 0644, 1);
    data->philos = ft_malloc(data->num_philos * sizeof(t_philo));
    data->start_time = ft_get_current_time();
    data->i = 0;
    i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].time_to_die = data->time_to_die;
        data->philos[i].time_to_eat = data->time_to_eat;
        data->philos[i].time_to_sleep = data->time_to_sleep;
        data->philos[i].num_to_eat = data->num_to_eat;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].data = data;
        i++;
    }
}

void ft_usleep(long time_in_ms)
{
    long start_time = ft_get_current_time();
    while (ft_get_current_time() - start_time < time_in_ms)
        usleep(500);
}

void    ft_print_status(t_philo *philo, char *status)
{
    ssize_t  current_time;

    current_time = ft_get_current_time();
    sem_wait(philo->data->print);
    if (ft_get_current_time() - philo->last_meal > philo->time_to_die)
    {
        printf("%ld\t%ld\tdied\n", current_time - philo->data->start_time, philo->id);
        sem_post(philo->data->monitor);
        while(1)
        {}
    }
    printf("%ld\t%ld\t%s\n", current_time - philo->data->start_time, philo->id, status);
    sem_post(philo->data->print);
}

void ft_philosopher_routine(t_philo *philo)
{
    while (1)
    {
        if ((philo->num_to_eat == 0) || (ft_get_current_time() - philo->last_meal > philo->time_to_die))
        {
            sem_post(philo->data->monitor);
            ft_exit(0);
        }
        sem_wait(philo->data->forks);
        ft_print_status(philo, "has taken a fork");
        sem_wait(philo->data->forks);
        ft_print_status(philo, "has taken a fork");
        ft_print_status(philo, "is eating");
        philo->last_meal = ft_get_current_time();
        ft_usleep(philo->time_to_eat);
        if (philo->num_to_eat > 0)
            philo->num_to_eat--;
        sem_post(philo->data->forks);
        sem_post(philo->data->forks);
        ft_print_status(philo, "is sleeping");
        ft_usleep(philo->time_to_sleep);
        ft_print_status(philo, "is thinking");
    }
}

void    ft_philo_one(t_philo *philo)
{
    sem_wait(philo->data->forks);
    ft_print_status(philo, "has taken a fork");   
    sem_post(philo->data->forks);
    ft_usleep(philo->time_to_die);
    printf("%ld\t%ld\tdied\n", ft_get_current_time() - philo->data->start_time, philo->id);
    sem_post(philo->data->monitor);
}

void    ft_create_processes(t_data *data)
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

int main(int ac, char **av)
{
    t_data  data;

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
