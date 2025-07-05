/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:36 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/05 19:28:56 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	destroy_mutexes(t_data *data)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&data->print_mutex);
// 	pthread_mutex_destroy(&data->death_mutex);
// 	pthread_mutex_destroy(&data->philos->lock_last_meal);
// 	pthread_mutex_destroy(&data->philos->lock_meals);	
// }

void destroy_global_mutexes(t_data *data)
{
    unsigned int i = 0;
    
    // Destroy fork mutexes
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
}

void destroy_mutexes(t_data *data)
{
    unsigned int i = 0;

    if (data->philos)
    {
        while (i < data->nb_philo)
        {
            pthread_mutex_destroy(&data->philos[i].lock_last_meal);
            pthread_mutex_destroy(&data->philos[i].lock_meals);
            i++;
        }
    }
    destroy_global_mutexes(data);
}