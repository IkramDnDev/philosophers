/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:48:54 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/08 18:13:59 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, TAKING_FORK);
	pthread_mutex_unlock(philo->left_fork);
	philo_sleep(philo->data->time_to_die);
	return (NULL);
}

static void	execute_lifecycle(t_philo *philo)
{
	take_forks(philo);
	eat(philo);
	release_forks(philo);
	print_msg(philo, SLEEPING);
	philo_sleep(philo->data->time_to_sleep);
	print_msg(philo, THINKING);
	usleep(100);
}

static void	wait_start_time(t_philo *philo)
{
	while (get_timestamp() < philo->data->start_time)
		usleep(100);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->lock_last_meal);
	if (philo->id % 2 == 0)
		usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start_time(philo);
	while (is_alive(philo->data))
	{
		if (philo->data->nb_philo == 1)
			return (handle_one_philo(philo));
		else
		{
			if (philo->data->nb_must_eat != -1)
			{
				pthread_mutex_lock(&philo->lock_meals);
				if (philo->meals_eaten >= philo->data->nb_must_eat)
				{
					pthread_mutex_unlock(&philo->lock_meals);
					return (NULL);
				}
				pthread_mutex_unlock(&philo->lock_meals);
			}
			execute_lifecycle(philo);
		}
	}
	return (NULL);
}
