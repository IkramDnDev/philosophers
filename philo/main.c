/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:14 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/16 10:38:44 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static int	create_threads(t_data *data)
{
	unsigned int	i;
	t_philo			*philos;

	philos = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			write(2, "Error: create threads failed\n", 29);
			destroy_data_mutexes(data);
			destroy_philo_mutexes(data);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	detach_threads(t_data *data)
{
	unsigned int	i;
	t_philo			*philos;

	philos = data->philos;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_detach(philos[i].thread) != 0)
		{
			write(2, "Error: detach threads failed\n", 28);
			destroy_data_mutexes(data);
			destroy_philo_mutexes(data);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_monitor(t_data *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		write(2, "Error: create monitor thread failed\n", 36);
		destroy_data_mutexes(data);
		destroy_philo_mutexes(data);
		return (0);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		write(2, "Error: join monitor thread failed\n", 34);
		destroy_data_mutexes(data);
		destroy_philo_mutexes(data);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		ft_is_valid_arguments(ac, av);
		if (!intialisation(ac, av, &data))
		{
			write(2, "Error: fill data failed\n", 25);
			return (1);
		}
		if (!create_threads(&data))
			return (1);
		if (!init_monitor(&data))
			return (1);
		if (!detach_threads(&data))
			return (1);
		usleep(100000);
		destroy_data_mutexes(&data);
		destroy_philo_mutexes(&data);
	}
	else
		error_usage();
	return (0);
}
