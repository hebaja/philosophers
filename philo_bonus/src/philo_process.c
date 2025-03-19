/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:49:12 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/17 18:01:15 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	case_one_philo(t_table *table, t_philo *philo)
{
	sem_post(table->forks_sem);
	improved_usleep(philo->time_to_die, table);
	philo->dead = 1;
	*philo->dead_flag = 1;
	print_dead_msg("died", table, philo);
	exit(EXIT_FAILURE);
}

void	philo_act(t_table *table, t_philo *philo)
{
	sem_wait(table->forks_sem);
	print_msg("has taken a fork", philo);
	if (table->philos_len == 1)
		case_one_philo(table, philo);
	sem_wait(table->forks_sem);
	if (philo_is_dead(table, philo) || table->dead_flag)
	{
		sem_post(table->forks_sem);
		sem_post(table->forks_sem);
	}
	print_msg("has taken a fork", philo);
	philo_eat(table, philo);
	philo_sleep(table, philo);
	philo_think(table, philo);
}

int	philo_process(int i, t_table *table, t_philo *philo)
{
	if (i % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo_is_dead(table, philo) || table->dead_flag)
			exit(EXIT_FAILURE);
		if (philo->times_to_eat_len != 0
			&& (philo->meals_had == philo->times_to_eat_len))
			break ;
		philo_act(table, philo);
	}
	exit(EXIT_SUCCESS);
}
