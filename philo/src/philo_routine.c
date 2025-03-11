/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/11 00:08:32 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philos_alive(t_philo *philo)
{
	int	res;

	res = 1;
	pthread_mutex_lock(philo->is_dead_key);
	if (*philo->is_dead)
		res = 0;
	pthread_mutex_unlock(philo->is_dead_key);
	return (res);
}

void	case_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", philo);
	improved_usleep(philo->time_to_die, philo);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->nbr_philos == 1)
	{
		case_one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(20);
	while (philos_alive(philo))
	{
		if (!philos_alive(philo) || (philo->nbr_times_to_eat != 0
			&& philo->meals_had >= philo->nbr_times_to_eat))
			break ;
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
