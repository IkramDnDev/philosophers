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

void philo_sleep(long time)
{
    long wake_up;
    wake_up = get_timestamp() + time;
    while (get_timestamp() < wake_up)
    {
        usleep(200);
    }
    //active sleeping thecnique
}

void *handle_one_philo(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_msg(philo, TAKING_FORK);
    pthread_mutex_unlock(philo->left_fork);
    philo_sleep(philo->data->time_to_die);
    print_msg(philo, DIED);
    pthread_mutex_unlock(philo->left_fork);
    return (NULL);
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    while (get_timestamp() < philo->data->start_time)
        continue;
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
	// printf("i'm philo number : %d\n", ((t_philo *)philo)->id);
	return (NULL);
}
