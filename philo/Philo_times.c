#include "Philosophers.h"

ssize_t ft_get_current_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_usleep(ssize_t time_in_ms)
{
    ssize_t current_time ;

    current_time = ft_get_current_time();
    while (ft_get_current_time() - current_time < time_in_ms)
        usleep(100);
}
