/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:01:57 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/11 17:54:55 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_alive(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->alive;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}

int	all_philosophers_satisfied(t_data *data)
{
	unsigned int	i;
	unsigned int	satisfied_count;

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
	return (satisfied_count == data->nb_philo);
}

static void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->alive = 0;
	pthread_mutex_unlock(&data->death_mutex);
}

static int	has_philo_died(t_data *data)
{
	unsigned int	i;
	t_philo			*philo;
	long			time_since_meal;
	int				is_eating;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = &data->philos[i];
		pthread_mutex_lock(&philo->lock_last_meal);
		time_since_meal = get_timestamp() - philo->last_meal;
		is_eating = philo->eating;
		pthread_mutex_unlock(&philo->lock_last_meal);
		if (time_since_meal > data->time_to_die && !is_eating)
		{
			print_msg(philo, DIED);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (is_alive(data))
	{
		if (all_philosophers_satisfied(data))
		{
			stop_simulation(data);
			return (NULL);
		}
		if (has_philo_died(data))
		{
			stop_simulation(data);
			return (NULL);
		}
	}
	return (NULL);
}
