#include "../include/philo.h"

void	release_forks(t_philo *philo, int is_both)
{
	if (is_both)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
		pthread_mutex_unlock(philo->right_fork);
}

void smart_sleep(int duration, t_philo *philo)
{
    size_t start_time = get_current_time();
    while ((get_current_time() - start_time) < duration)
    {
        if (!philos_alive(philo))
            return;  // Stop sleeping if philosopher is dead
        usleep(100); // Sleep in small increments
    }
}

int	philo_sleep(t_philo *philo)
{
	if (!philos_alive(philo))
		return (0);
	print_msg("is sleeping", philo);
	usleep(philo->time_to_sleep);
	// smart_sleep(philo->time_to_sleep, philo);
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (!philos_alive(philo))
		return (0);
	print_msg("is thinking", philo);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);


	if (!philos_alive(philo))
	{
		release_forks(philo, 0);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_msg("has taken a fork", philo);
	if (philo->nbr_philos == 1)
	{
		usleep(philo->time_to_die);
		printf("killing\n");
		release_forks(philo, 0);
		philo->dead = 1;
		*philo->is_dead = 1;
		return (0);
	}
	pthread_mutex_lock(philo->left_fork);
	if (!philos_alive(philo))
	{
		release_forks(philo, 1);
		return (0);
	}
	print_msg("has taken a fork", philo);
	philo->is_eating = 1;
	print_msg("is eating", philo);
	pthread_mutex_lock(philo->is_eating_key);
	philo->meals_had++;
	philo->last_time_ate = get_current_time();
	pthread_mutex_unlock(philo->is_eating_key);
	usleep(philo->time_to_eat);
	release_forks(philo, 1);
	philo->is_eating = 0;
	return (1);
}
