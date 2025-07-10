/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:36 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/10 13:39:26 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_data_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
}

void	destroy_philo_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->philos[i].lock_last_meal);
			pthread_mutex_destroy(&data->philos[i].lock_meals);
			i++;
		}
	}
	free(data->philos);
}
