/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:01:57 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/04 12:43:57 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\n')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (INT_MAX - (str[i] - '0')) / 10)
			error_input_digit();
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data			*data;
	t_philo			*philo;
	unsigned int	i;
	long			time_since_meal;

	data = (t_data *)arg;
	while (is_alive(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			philo = &data->philos[i];
			pthread_mutex_lock(&philo->lock_last_meal);
			time_since_meal = get_timestamp() - philo->last_meal;
			pthread_mutex_unlock(&philo->lock_last_meal);
			if (time_since_meal >= data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->alive = 0;
				pthread_mutex_unlock(&data->death_mutex);
				print_msg(philo, DIED);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	is_alive(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->alive;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}
