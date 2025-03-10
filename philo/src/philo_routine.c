/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/09 20:34:26 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (!philos_alive(philo))
	{
		release_forks(philo, 0);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_msg("has taken a fork r", philo);
	pthread_mutex_lock(philo->left_fork);
	if (!philos_alive(philo))
	{
		release_forks(philo, 1);
		return (0);
	}
	print_msg("has taken a fork l", philo);
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

int	philo_sleep(t_philo *philo)
{
	if (!philos_alive(philo))
		return (0);
	print_msg("is sleeping", philo);
	usleep(philo->time_to_sleep);
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (!philos_alive(philo))
		return (0);
	print_msg("is thinking", philo);
	return (1);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (philos_alive(philo))
	{
		if (!philos_alive(philo)
			|| (philo->nbr_times_to_eat != 0
				&& philo->meals_had >= philo->nbr_times_to_eat))
			break ;
		if (philo->id % 2 == 0)
			usleep(10);
		if (!philos_alive(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (NULL);
}
