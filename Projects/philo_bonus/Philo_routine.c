#include "Philo_header.h"

void	ft_print_status(t_philo *philo, char *status)
{
	size_t	current_time;

	current_time = ft_get_current_time();
	sem_wait(philo->data->print);
	if (ft_get_current_time() - philo->last_meal > philo->time_to_die)
	{
		printf("%ld\t%ld\tdied\n", current_time - philo->data->start_time,
			philo->id);
		sem_post(philo->data->monitor);
		while (1)
		{
		}
	}
	printf("%ld\t%ld\t%s\n", current_time - philo->data->start_time, philo->id,
		status);
	sem_post(philo->data->print);
}

void	ft_philosopher_routine(t_philo *philo)
{
	while (1)
	{
		if ((philo->num_to_eat == 0) || (ft_get_current_time()
				- philo->last_meal > philo->time_to_die))
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

void	ft_philo_one(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_print_status(philo, "has taken a fork");
	sem_post(philo->data->forks);
	ft_usleep(philo->time_to_die);
	printf("%ld\t%ld\tdied\n", ft_get_current_time() - philo->data->start_time,
		philo->id);
	sem_post(philo->data->monitor);
}
