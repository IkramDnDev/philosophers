#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int id;
    int meals_eaten;
    long last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    t_data *data;
} t_philo;

struct s_data
{
    int nb_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int nb_must_eat;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philo *philos;
};

// Get current timestamp in milliseconds
long get_timestamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void safe_print(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d %s\n", get_timestamp() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        safe_print(philo, "has taken right fork");
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken left fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken left fork");
        pthread_mutex_lock(philo->right_fork);
        safe_print(philo, "has taken right fork");
    }
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void eat(t_philo *philo)
{
    safe_print(philo, "is eating");
    philo->last_meal = get_timestamp();
    philo->meals_eaten++;
    usleep(philo->data->time_to_eat * 1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Synchronize start
    while (get_timestamp() < philo->data->start_time)
        usleep(100);

    // Small delay for even philosophers
    if (philo->id % 2 == 0)
        usleep(1000);

    while (1)
    {
        take_forks(philo);
        eat(philo);
        release_forks(philo);

        if (philo->data->nb_must_eat != -1 &&
            philo->meals_eaten >= philo->data->nb_must_eat)
            break;

        safe_print(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);

        safe_print(philo, "is thinking");
    }
    return (NULL);
}

int init_data(t_data *data, int argc, char **argv)
{
    data->nb_philo = atoi(argv[1]);
    data->time_to_die = atol(argv[2]);
    data->time_to_eat = atol(argv[3]);
    data->time_to_sleep = atol(argv[4]);

    if (argc == 6)
        data->nb_must_eat = atoi(argv[5]);
    else
        data->nb_must_eat = -1;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    data->philos = malloc(sizeof(t_philo) * data->nb_philo);
    pthread_mutex_init(&data->print_mutex, NULL);
    for (int i = 0; i < data->nb_philo; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    for (int i = 0; i < data->nb_philo; i++)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
        data->philos[i].data = data;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [nb_must_eat]\n");
        return (1);
    }

    if (!init_data(&data, argc, argv))
        return (1);

    // Set global start time
    data.start_time = get_timestamp() + 1000;

    for (int i = 0; i < data.nb_philo; i++)
        pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);

    for (int i = 0; i < data.nb_philo; i++)
        pthread_join(data.philos[i].thread, NULL);

    // Destroy mutexes and free
    for (int i = 0; i < data.nb_philo; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.print_mutex);
    free(data.forks);
    free(data.philos);
    return (0);
}
