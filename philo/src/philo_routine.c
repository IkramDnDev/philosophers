/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:48:54 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/19 20:28:41 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
       // Optional sync start
    // while (get_timestamp() < philo->data->start_time)
    //     usleep(100);
    
    // // Optional delay for even philosophers
    // if (philo->id % 2 == 0)
    //     usleep(1000);
    // while (philo->data->alive)
    // {
    //     // Do: think → take forks → eat → release forks → sleep

    //     if (philo->data->nb_must_eat != -1
    //         && philo->meals_eaten >= philo->data->nb_must_eat)
    //         break;
    // }
	printf("i'm philo number : %d\n", ((t_philo *)philo)->id);
	return (NULL);
}
