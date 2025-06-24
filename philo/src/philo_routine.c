/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:48:54 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/23 18:18:41 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *handle_one_philo(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    while (get_timestamp() < philo->data->start_time)
        usleep(100);
    if (philo->id % 2 == 0)
        usleep(1000);
    while (philo->data->alive)
    {
        if (philo->data->nb_philo == 1)
            return(handle_one_philo(philo));
        if (philo->data->nb_must_eat != -1
            && philo->meals_eaten >= philo->data->nb_must_eat)
            break;
    }
	printf("i'm philo number : %d\n", ((t_philo *)philo)->id);
	return (NULL);
}
