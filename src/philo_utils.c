/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:01:57 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/07 14:18:16 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	all_philosophers_satisfied(t_data *data)
{
	unsigned int	i;
	int				satisfied_count;

	satisfied_count = 0;
	if (data->nb_must_eat == -1)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].lock_meals);
		if (data->philos[i].meals_eaten >= data->nb_must_eat)
			satisfied_count++;
		pthread_mutex_unlock(&data->philos[i].lock_meals);
		i++;
	}
	return (satisfied_count == (int)data->nb_philo);
}

void	*monitor_routine(void *arg)
{
	t_data			*data;
	t_philo			*philo;
	unsigned int	i;
	long			time_since_meal;

	data = (t_data *)arg;
	usleep(1000);
	while (is_alive(data))
	{
		if (all_philosophers_satisfied(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->alive = 0;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		i = 0;
		while (i < data->nb_philo)
		{
			philo = &data->philos[i];
			pthread_mutex_lock(&philo->lock_last_meal);
			time_since_meal = get_timestamp() - philo->last_meal;
			pthread_mutex_unlock(&philo->lock_last_meal);
			if (time_since_meal >= data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->alive = 0;
				pthread_mutex_unlock(&data->death_mutex);
				print_msg(philo, DIED);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	is_alive(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->alive;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}
