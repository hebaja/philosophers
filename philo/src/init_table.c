/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:20 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/10 23:21:06 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean(t_table *table)
{
	pthread_mutex_destroy(&table->is_dead_key);
	pthread_mutex_destroy(&table->is_eating_key);
	pthread_mutex_destroy(&table->printing_key);
	free(table->philos);
	free(table->forks);
}

void	init_table(t_table *table)
{
	int	i;

	pthread_create(&table->table_t, NULL, &monitor, table);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_create(&table->philos[i].philo_t, NULL,
			&philo_routine, &table->philos[i]);
	pthread_join(table->table_t, NULL);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philos[i].philo_t, NULL);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_mutex_destroy(&table->forks[i]);
	clean(table);
}
