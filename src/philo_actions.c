/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:11:27 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/08 18:12:27 by idahhan          ###   ########.fr       */
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
