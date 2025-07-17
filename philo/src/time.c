/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:06:43 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/11 11:32:24 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_sleep(long time, t_data *data)
{
	long	wake_up;

	wake_up = get_timestamp() + time;
	while (get_timestamp() < wake_up)
	{
		if (!is_alive(data))
			break ;
		usleep(100);
	}
}
