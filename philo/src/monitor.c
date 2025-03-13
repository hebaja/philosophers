/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:49 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/12 22:52:17 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philos_ate_enough(t_philo *philos)
{
	int		i;
	int		nbr_philos;

	i = -1;
	nbr_philos = philos[0].nbr_philos;
	while (++i < nbr_philos)
	{
		if (philos[i].meals_had < philos->nbr_times_to_eat)
			return (0);
	}
	i = -1;
	return (1);
}

int	philo_dead(t_philo *philo)
{
	size_t	current_time;

	pthread_mutex_lock(philo->is_eating_key);
	current_time = get_current_time();
	if (current_time - philo->last_time_ate
		>= philo->time_to_die && philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->is_eating_key);
		return (1);
	}
	pthread_mutex_unlock(philo->is_eating_key);
	return (0);
}

int	dead_monitor(t_philo *philos)
{
	int		i;

	i = -1;
	while (++i < philos[0].nbr_philos)
	{
		if (philo_dead(&philos[i]))
		{
			pthread_mutex_lock(philos[i].is_dead_key);
			*philos[i].a_dead_philo = 1;
			philos[i].dead = 1;
			pthread_mutex_unlock(philos[i].is_dead_key);
			print_msg("died", &philos[i]);
			return (1);
		}
	}
	return (0);
}

void	*monitor(void *table_ptr)
{
	t_table	*table;

	table = (t_table *)table_ptr;
	while (1)
	{
		if (table->philos[0].nbr_times_to_eat != 0)
			if (philos_ate_enough(table->philos))
				break ;
		if (dead_monitor(table->philos))
			break ;
	}
	return (NULL);
}
