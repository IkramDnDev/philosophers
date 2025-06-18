/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:14 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/18 20:40:25 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_data(t_data *data)
{
	printf("Number of Philosophers: %d\n", data->nb_philo);
	printf("Time to Die: %ld\n", data->time_to_die);
	printf("Time to Eat: %ld\n", data->time_to_eat);
	printf("Time to Sleep: %ld\n", data->time_to_sleep);
	if (data->has_optional_arg)
		printf("Number of Must Eat: %d\n", data->nb_must_eat);
	else
		printf("No optional argument for number of must eat.\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		ft_is_valid_arguments(ac, av);
		if (!intialisation(ac, av, &data))
			return (write(2, "Error: fill data failed\n", 25), 1);
	}
	else
		error_usage();
	return (0);
}
