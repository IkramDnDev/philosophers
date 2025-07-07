/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:18:25 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/07 14:18:26 by idahhan          ###   ########.fr       */
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
