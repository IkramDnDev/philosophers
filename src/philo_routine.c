/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:48:54 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/07 14:16:10 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, TAKING_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, TAKING_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, TAKING_FORK);
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eat(t_philo *philo)
{
	print_msg(philo, EATING);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->lock_last_meal);
	pthread_mutex_lock(&philo->lock_meals);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->lock_meals);
	philo_sleep(philo->data->time_to_eat);
}

void	*handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, TAKING_FORK);
	pthread_mutex_unlock(philo->left_fork);
	philo_sleep(philo->data->time_to_die);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_timestamp() < philo->data->start_time)
		usleep(100);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->lock_last_meal);
	if (philo->id % 2 == 0)
		usleep(1000);
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
			take_forks(philo);
			eat(philo);
			release_forks(philo);
			print_msg(philo, SLEEPING);
			philo_sleep(philo->data->time_to_sleep);
			print_msg(philo, THINKING);
			usleep(100);
		}
	}
	return (NULL);
}
