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
			usleep(100);
		if (!philos_alive(philo))
			break ;
		if (!philo_eat(philo))
		{
			print_msg("eat return", philo);
			break ;
		}
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	print_msg("routine return", philo);
	return (NULL);
}
