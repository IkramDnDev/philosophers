/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:05 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/16 11:05:01 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_input_digit(void)
{
	write(2, "philo: invalid input: ", 23);
	write(2, "not a valid unsigned integer between 0 and 2147483647.\n", 55);
	exit(1);
}

void	error_num_philo(void)
{
	write(2, "philo: invalid input: ", 23);
	write(2, "number of philosophers should be greater than 0.\n", 50);
	exit(1);
}

void	error_usage(void)
{
	write(2, "philo: usage: ", 13);
	write(2, "./philo <number_of_philosophers> <time_to_die> ", 48);
	write(2, "<time_to_eat> <time_to_sleep> ", 31);
	write(2, "[number_of_times_each_philosopher_must_eat]\n", 45);
	exit(1);
}

static void	print_message(t_philo *philo, t_status status)
{
	if (status == TAKING_FORK)
	{
		printf("has taken a fork\n");
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else if (status == EATING)
	{
		printf("is eating\n");
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else if (status == SLEEPING)
	{
		printf("is sleeping\n");
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else if (status == THINKING)
	{
		printf("is thinking\n");
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else if (status == DIED)
		printf("died\n");
}

void	print_msg(t_philo *philo, int status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_timestamp() - philo->data->start_time;
	if (!is_alive(philo->data) && status != DIED)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d ", timestamp, philo->id);
	print_message(philo, status);
}
