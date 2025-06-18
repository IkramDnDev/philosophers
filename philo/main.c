#include "philo.h"

void	print_data(t_data *data)
{
	printf("Number of Philosophers: %d\n", data->nb_philo);
	printf("Time to Die: %d\n", data->time_to_die);
	printf("Time to Eat: %d\n", data->time_to_eat);
	printf("Time to Sleep: %d\n", data->time_to_sleep);
	if (data->has_optional_arg)
		printf("Number of Must Eat: %d\n", data->nb_must_eat);
	else
		printf("No optional argument for number of must eat.\n");
}

int main(int ac, char **av)
{
    t_data data;
    if (ac == 5 || ac == 6)
    {
        ft_is_valid_arguments(ac, av);
        if (!fill_data(&data, ac, av))
		    return (write(2, "Error: fill data failed\n", 25), 1);
        print_data(&data);
    }
    else
        error_usage();
    return (0);
}
