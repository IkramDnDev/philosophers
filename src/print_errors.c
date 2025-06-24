/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:05 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/18 20:46:30 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_input_digit(void)
{
	printf("philo: invalid input: not a valid unsigned integer between 0 and 2147483647.\n");
	exit(1);
}

void	error_num_philo(void)
{
	printf("philo: invalid input: number of philosophers should be greater than 0.\n");
	exit(1);
}

void	error_usage(void)
{
	printf("philo: usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

void print_msg(t_philo *philo, t_status status)
{
	long timestamp;
	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_timestamp() - philo->data->start_time;
	if (philo->data->alive || status == DIED)
	{
		printf("%ld %d ", timestamp, philo->id);
        if (status == TAKING_FORK)
            printf("has taken a fork\n");
        else if (status == EATING)
            printf("is eating\n");
        else if (status == SLEEPING)
            printf("is sleeping\n");
        else if (status == THINKING)
            printf("is thinking\n");
        else if (status == DIED)
            printf("died\n");
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
