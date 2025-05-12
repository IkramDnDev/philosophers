#include "philo.h"

static int ft_all_is_digits(char *str)
{
    size_t i = 0;
    while (i < ft_strlen(str))
    {
        if (!ft_isdigit(str[i]))
            return(0);
        i++;   
    }
    return(1);
}

int ft_is_valid_arguments(int ac, char **av)
{
    int i = 1;
    int n;
    while (i < ac)
    {
        if (!ft_all_is_digits(av[i]))
            return(0);
        n = ft_atoi(av[i]);
        if (n <= 0 || n > INT_MAX)
            return(0);
        i++;
    }
    return(1);
}

int fill_data(t_data *data, int ac, char **av)
{
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
    {
        data->nb_must_eat = ft_atoi(av[5]);
        data->has_optional_arg = 1;
    }
    else
        data->has_optional_arg = 0;
    return(1);
}
