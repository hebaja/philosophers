/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:05 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/17 18:12:15 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	philo_is_dead(t_table *table, t_philo *philo)
{
	size_t	current_time;

	sem_wait(table->meal_sem);
	current_time = get_current_time();
	if (current_time - philo->last_time_meal
		> philo->time_to_die && philo->is_eating == 0)
	{
		if (table->dead_flag)
			return (0);
		sem_wait(table->dead_sem);
		table->dead_flag = 1;
		sem_post(table->dead_sem);
		print_dead_msg("died", table, philo);
		sem_post(table->meal_sem);
		return (1);
	}
	sem_post(table->meal_sem);
	return (0);
}

void	set_philo_data(t_table *table, t_philo *philo, char **args, int i)
{
	philo->id = i + 1;
	philo->philos_len = table->philos_len;
	philo->dead = 0;
	philo->is_eating = 0;
	philo->is_sleeping = 0;
	philo->meals_had = 0;
	philo->start_time = table->start_time;
	philo->last_time_meal = get_current_time();
	philo->time_to_die = ft_atoi(args[2]);
	philo->time_to_eat = ft_atoi(args[3]);
	philo->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		philo->times_to_eat_len = ft_atoi(args[5]);
	else
		philo->times_to_eat_len = 0;
}

int	build_philos(t_table *table, char **args)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * table->philos_len);
	if (!philos)
		return (0);
	philos->dead_flag = &table->dead_flag;
	while (++i < table->philos_len)
		set_philo_data(table, &philos[i], args, i);
	table->philos = philos;
	return (1);
}
