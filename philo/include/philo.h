/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:13:43 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/22 15:41:07 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	unsigned int	nb_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_must_eat;                                                                                                   
	long			start_time; // Timestamp when simulation starts (used to calculate elapsed time for printing & death checking).
	int 			alive; //	Flag to know if someone died (0 = dead,1 = alive).
	pthread_mutex_t *forks;      //	Array of mutexes — one mutex per fork.
	pthread_mutex_t print_mutex; // Mutex to protect printing (avoid mixed messages in terminal).
	t_philo			*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;  //	Counter for how many times this philosopher has eaten (used if nb_must_eat provided).
	long			last_meal; //the timestamp (in ms) when this philosopher last started eating.
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
}					t_philo;


int					ft_isdigit(int n);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
void				ft_is_valid_arguments(int ac, char **av);
void				error_input_digit(void);
void				error_num_philo(void);
void				error_usage(void);
int					intialisation(int ac, char **av, t_data *data);
void				print_data(t_data *data);
void				*philo_routine(void *philo);
void				destroy_mutexes(t_data *data);
long				get_timestamp(void);
#endif