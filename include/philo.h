/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:13:43 by idahhan           #+#    #+#             */
/*   Updated: 2025/07/10 13:39:11 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}						t_status;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	unsigned int		nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					nb_must_eat;
	long				start_time;
	int					alive;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	unsigned int		id;
	int					meals_eaten;
	long				last_meal;
	pthread_mutex_t		lock_meals;
	pthread_mutex_t		lock_last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

int						ft_isdigit(int n);
int						ft_atoi(const char *str);
size_t					ft_strlen(const char *s);
void					ft_is_valid_arguments(int ac, char **av);
void					error_input_digit(void);
void					error_num_philo(void);
void					error_usage(void);
int						intialisation(int ac, char **av, t_data *data);
void					*philo_routine(void *philo);
long					get_timestamp(void);
void					print_msg(t_philo *philo, t_status status);
void					*monitor_routine(void *arg);
int						is_alive(t_data *data);
void					philo_sleep(long time);
void					eat(t_philo *philo);
void					take_forks(t_philo *philo);
void					release_forks(t_philo *philo);
void					destroy_philo_mutexes(t_data *data);
void					destroy_data_mutexes(t_data *data);
#endif