/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:48:54 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/16 11:10:07 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, TAKING_FORK);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, TAKING_FORK);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock_last_meal);
	print_msg(philo, EATING);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->lock_last_meal);
	pthread_mutex_lock(&philo->lock_meals);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->lock_meals);
	philo_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock_last_meal);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	*handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, TAKING_FORK);
	pthread_mutex_unlock(philo->left_fork);
	philo_sleep(philo->data->time_to_die, philo->data);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_timestamp() < philo->data->start_time)
		usleep(100);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->lock_last_meal);
	if (philo->id % 2 == 0)
		philo_sleep(philo->data->time_to_eat / 2, philo->data);
	while (is_alive(philo->data) && !all_philosophers_satisfied(philo->data))
	{
		if (philo->data->nb_philo == 1)
			return (handle_one_philo(philo));
		else
		{
			eat(philo);
			print_msg(philo, SLEEPING);
			philo_sleep(philo->data->time_to_sleep, philo->data);
			print_msg(philo, THINKING);
		}
	}
	return (NULL);
}
