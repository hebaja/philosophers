/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:05 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/19 15:16:26 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_add_data(int i, t_philo *philos, t_table *table, char **args)
{
	philos[i].time_to_die = ft_atoi(args[2]);
	philos[i].time_to_eat = ft_atoi(args[3]);
	philos[i].time_to_sleep = ft_atoi(args[4]);
	philos[i].start_time = get_current_time();
	philos[i].last_time_ate = get_current_time();
	if (args[5])
		philos[i].nbr_times_to_eat = ft_atoi(args[5]);
	else
		philos[i].nbr_times_to_eat = 0;
	if (i == 0)
	{
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[table->nbr_philos - 1];
	}
	else
	{
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[i - 1];
	}
}

int	build_philos(t_table *table, char **args)
{
	int			i;
	t_philo		*philos;

	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * table->nbr_philos);
	if (!philos)
		return (0);
	while (++i < table->nbr_philos)
	{
		philos[i].id = i + 1;
		philos[i].nbr_philos = table->nbr_philos;
		philos[i].meals_had = 0;
		philos[i].is_eating = 0;
		philos[i].a_dead_philo = &table->is_dead_flag;
		philos[i].is_dead_key = &table->is_dead_key;
		philos[i].is_eating_key = &table->is_eating_key;
		philos[i].printing_key = &table->printing_key;
		set_add_data(i, philos, table, args);
	}
	table->philos = philos;
	return (1);
}

int	build_forks(t_table *table)
{
	int				i;
	t_fork			*forks;

	i = -1;
	forks = (t_fork *)malloc(
			sizeof(t_fork) * table->nbr_philos);
	if (!forks)
		return (0);
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&forks[i].key, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i].key);
			free(forks);
			return (0);
		}
		forks[i].id = i + 1;
		forks[i].locked = 0;
	}
	table->forks = forks;
	return (1);
}

int	build_keys(t_table *table)
{
	if (pthread_mutex_init(&table->is_dead_key, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->is_eating_key, NULL) != 0)
	{
		pthread_mutex_destroy(&table->is_dead_key);
		return (0);
	}
	if (pthread_mutex_init(&table->printing_key, NULL) != 0)
	{
		pthread_mutex_destroy(&table->is_dead_key);
		pthread_mutex_destroy(&table->is_eating_key);
		return (0);
	}
	if (!build_forks(table))
	{
		pthread_mutex_destroy(&table->is_dead_key);
		pthread_mutex_destroy(&table->is_eating_key);
		pthread_mutex_destroy(&table->printing_key);
		return (0);
	}
	return (1);
}
