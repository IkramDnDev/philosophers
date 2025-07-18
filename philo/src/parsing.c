/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:11 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/16 11:24:57 by idahhan          ###   ########.fr       */
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
	int		sig;

	(1) && (sig = 1, res = 0, i = 0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (INT_MAX - (str[i] - '0')) / 10)
			error_input_digit();
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		error_input_digit();
	return (res * sig);
}

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	return (0);
}

void	ft_is_valid_arguments(int ac, char **av)
{
	int	i;
	int	n;

	i = 1;
	if (ft_atoi(av[1]) < 1)
		error_num_philo();
	if (ft_atoi(av[2]) == 0 || ft_atoi(av[3]) == 0 || ft_atoi(av[4]) == 0)
		exit(1);
	while (i < ac)
	{
		n = ft_atoi(av[i]);
		if (n < 0)
			error_input_digit();
		i++;
	}
}
