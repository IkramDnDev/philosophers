#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

typedef struct s_data {
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int	nb_must_eat;
    int	has_optional_arg;
}       t_data;

int	ft_isdigit(int n);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int ft_is_valid_arguments(int ac, char **av);
int fill_data(t_data *data, int ac, char **av);

#endif