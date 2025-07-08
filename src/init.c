/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:01:53 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/08 15:16:27 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else if (ac == 5)
		data->nb_must_eat = -1;
	data->start_time = get_timestamp() + 1000;
	data->alive = 1;
	data->forks = NULL;
	data->philos = NULL;
}

static int	init_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].thread = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].lock_last_meal, NULL) != 0
			|| pthread_mutex_init(&data->philos[i].lock_meals, NULL) != 0)
		{
			destroy_data_mutexes(data);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_data_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	intialisation(int ac, char **av, t_data *data)
{
	init_data(ac, av, data);
	if (!init_data_mutexes(data) || !init_philos(data))
		return (0);
	return (1);
}
