#include "Philosophers.h"

int main(int ac, char **av)
{
    t_philo_config  args;

    if (ac < 5 || ac > 6)
        ft_print_usage_and_exit();
    ft_parse_philo(ac, av, &args);
    printf("Nadiiiiiii\n");
}
