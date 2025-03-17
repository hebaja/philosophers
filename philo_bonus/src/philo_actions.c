/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:54 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/12 16:47:01 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

int	philo_think(t_philo *philo)
{
	if (!philos_alive(philo))
		return (0);
	print_msg("is thinking", philo);
	return (1);
}

// int	philo_sleep(t_philo *philo)
// {
// 	if (!philos_alive(philo))
// 		return (0);
// 	print_msg("is sleeping", philo);
// 	improved_usleep(philo->time_to_sleep, philo);
// 	return (1);
// }

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
	improved_usleep(philo->time_to_eat, philo);
	release_forks(philo, 1);
	philo->is_eating = 0;
	return (1);
}
