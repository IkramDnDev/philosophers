/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:02:11 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/18 19:16:23 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_all_is_digits(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_is_valid_arguments(int ac, char **av)
{
	int	i;
	int	n;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 250)
			error_num_philo();
		if (!ft_all_is_digits(av[i]))
			error_input_digit();
		n = ft_atoi(av[i]);
		if (n < 0)
			error_input_digit();
		i++;
	}
}
