/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:54 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/17 17:43:10 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	philo_think(t_table *table, t_philo *philo)
{
	if (table->dead_flag)
		exit(EXIT_FAILURE);
	print_msg("is thinking", philo);
}

void	philo_sleep(t_table *table, t_philo *philo)
{
	if (table->dead_flag)
		exit(EXIT_FAILURE);
	print_msg("is sleeping", philo);
	improved_usleep(philo->time_to_sleep, table);
}

void	philo_eat(t_table *table, t_philo *philo, sem_t *fork_l, sem_t *fork_r)
{
	philo->is_eating = 1;
	print_msg("is eating", philo);
	sem_wait(table->meal_sem);
	philo->meals_had++;
	philo->last_time_meal = get_current_time();
	sem_post(table->meal_sem);
	improved_usleep(philo->time_to_eat, table);
	sem_post(fork_l);
	sem_post(fork_r);
	philo->is_eating = 0;
}
