/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:14 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/08 15:26:38 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	f(void)
{
	system("leaks philo");
}

int	create_threads(t_data *data)
{
	unsigned int	i;
	t_philo			*philos;

	philos = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	join_threads(t_data *data)
{
	unsigned int	i;
	t_philo			*philos;

	philos = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor_thread;

	// atexit(f);
	if (ac == 5 || ac == 6)
	{
		ft_is_valid_arguments(ac, av);
		if (!intialisation(ac, av, &data))
			return (write(2, "Error: fill data failed\n", 25), 1);
		if (!create_threads(&data))
			return (write(2, "Error: create threads failed\n", 25), 1);
		pthread_create(&monitor_thread, NULL, monitor_routine, &data);
		pthread_join(monitor_thread, NULL);
		if (!join_threads(&data))
			return (write(2, "Error: join threads failed\n", 25), 1);
		destroy_data_mutexes(&data);
		destroy_philo_mutexes(&data);
	}
	else
		error_usage();
	return (0);
}
