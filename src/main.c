/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:14 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/20 20:31:46 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void f()
{
	system("leaks philo");
}
void	print_data(t_data *data)
{
	printf("Number of Philosophers: %d\n", data->nb_philo);
	printf("Time to Die: %ld\n", data->time_to_die);
	printf("Time to Eat: %ld\n", data->time_to_eat);
	printf("Time to Sleep: %ld\n", data->time_to_sleep);
	if (data->nb_must_eat != -1)
		printf("Number of Must Eat: %d\n", data->nb_must_eat);
	else
		printf("No optional argument for number of must eat.\n");
}

int create_threads(t_data *data)
{
	unsigned int i;
	t_philo *philos;
	
	philos = data->philos;
	data->start_time = get_timestamp() + 1000;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int joi_threads(t_data *data)
{
	unsigned int i;
	t_philo *philos;

	philos = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return(0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	// atexit(f);
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		ft_is_valid_arguments(ac, av);
		if (!intialisation(ac, av, &data))
			return (write(2, "Error: fill data failed\n", 25), 1);
		if (!create_threads(&data))
			return (write(2, "Error: create threads failed\n", 25), 1);
		if(!joi_threads(&data))
			return (write(2, "Error: join threads failed\n", 25), 1);
		// print_data(&data);
		destroy_mutexes(&data);
		free(data.philos);
		free(data.forks);
	}
	else
		error_usage();
	return (0);
}
