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
	improved_usleep(philo->time_to_die, table);
	philo->dead = 1;
	*philo->dead_flag = 1;
	print_dead_msg("died", table, philo);
	exit(EXIT_FAILURE);
}

void	case_philo_dies(sem_t *fork_l, sem_t *fork_r, int both)
{
	if (both)
	{
		sem_post(fork_l);
		sem_post(fork_r);
	}
	else
		sem_post(fork_l);
	exit(EXIT_FAILURE);
}

void	philo_act(t_table *table, t_philo *philo, sem_t *fork_l, sem_t *fork_r)
{
	sem_wait(fork_l);
	print_msg("took a fork", philo);
	if (table->philos_len == 1)
		case_one_philo(table, philo);
	sem_wait(fork_r);
	if (philo_is_dead(table, philo) || table->dead_flag)
		case_philo_dies(fork_l, fork_r, 1);
	print_msg("took a fork", philo);
	philo_eat(table, philo, fork_l, fork_r);
	philo_sleep(table, philo);
	philo_think(table, philo);
}

int	philo_process(int i, t_table *table, t_philo *philo)
{
	sem_t	*fork_l;
	sem_t	*fork_r;

	if (i % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo_is_dead(table, philo) || table->dead_flag)
			exit(EXIT_FAILURE);
		if (philo->times_to_eat_len != 0
			&& (philo->meals_had == philo->times_to_eat_len))
			break ;
		fork_l = table->forks[i].sem;
		if (i == 0)
			fork_r = table->forks[table->philos_len - 1].sem;
		else
			fork_r = table->forks[i - 1].sem;
		philo_act(table, philo, fork_l, fork_r);
	}
	exit(EXIT_SUCCESS);
}
