#include "philo.h"

void error_input_digit(void)
{
    printf("philo: invalid input: not a valid unsigned integer between 0 and 2147483647.\n");
    exit(1);
}

void error_num_philo(void)
{
    printf("philo: invalid input: there must be between 1 and 250 philosophers.\n");
    exit(1);
}

void error_usage(void)
{       
    printf("philo: usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
    exit(1);
}