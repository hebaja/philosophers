/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:54 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/19 18:24:31 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_think(t_philo *philo)
{
	size_t	time_to_think;

	time_to_think = (philo->time_to_eat * philo->nbr_philos) / 3;
	if (!philos_alive(philo))
		return (0);
	print_msg("is thinking", philo);
	usleep(time_to_think);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (!philos_alive(philo))
		return (0);
	print_msg("is sleeping", philo);
	improved_usleep(philo->time_to_sleep, philo);
	return (1);
}

int	get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->key);
		philo->right_fork->locked = 1;
		print_msg("has taken a fork", philo);
		pthread_mutex_lock(&philo->left_fork->key);
		philo->left_fork->locked = 1;
		print_msg("has taken a fork", philo);
		philo->left_fork->locked = 0;
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->key);
		philo->left_fork->locked = 1;
		print_msg("has taken a fork", philo);
		pthread_mutex_lock(&philo->right_fork->key);
		philo->right_fork->locked = 1;
		print_msg("has taken a fork", philo);
	}
	return (1);
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->left_fork->locked = 0;
		pthread_mutex_unlock(&philo->left_fork->key);
		philo->right_fork->locked = 0;
		pthread_mutex_unlock(&philo->right_fork->key);
	}
	else
	{
		philo->right_fork->locked = 0;
		pthread_mutex_unlock(&philo->right_fork->key);
		philo->left_fork->locked = 0;
		pthread_mutex_unlock(&philo->left_fork->key);
	}
}

int	philo_eat(t_philo *philo)
{
	if (philos_alive(philo))
	{
		get_forks(philo);
		if (!philos_alive(philo))
		{
			release_forks(philo);
			return (0);
		}
		philo->is_eating = 1;
		print_msg("is eating", philo);
		pthread_mutex_lock(philo->is_eating_key);
		philo->meals_had++;
		philo->last_time_ate = get_current_time();
		pthread_mutex_unlock(philo->is_eating_key);
		improved_usleep(philo->time_to_eat, philo);
		release_forks(philo);
		philo->is_eating = 0;
		return (1);
	}
	return (0);
}
