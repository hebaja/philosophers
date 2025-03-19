/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:20 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/17 18:20:41 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	clean_table(t_table *table)
{
	sem_close(table->print_sem);
	sem_close(table->meal_sem);
	sem_close(table->dead_sem);
	sem_close(table->forks_sem);
	sem_unlink(table->print_sem_name);
	sem_unlink(table->meal_sem_name);
	sem_unlink(table->dead_sem_name);
	sem_unlink(table->forks_sem_name);
	if (table->pids)
		free(table->pids);
	if (table->philos)
		free(table->philos);
}

int	build_table(t_table *table, char **args)
{
	table->dead_flag = 0;
	table->philos_len = ft_atoi(args[1]);
	table->start_time = get_current_time();
	table->print_sem_name = "/print";
	table->meal_sem_name = "/meal";
	table->dead_sem_name = "/dead";
	table->forks_sem_name = "/forks";
	table->print_sem = sem_open(table->print_sem_name, O_CREAT
			| O_EXCL, 0644, 1);
	table->meal_sem = sem_open(table->meal_sem_name, O_CREAT | O_EXCL, 0644, 1);
	table->dead_sem = sem_open(table->dead_sem_name, O_CREAT | O_EXCL, 0644, 1);
	table->forks_sem = sem_open(table->forks_sem_name, O_CREAT
			| O_EXCL, 0664, table->philos_len);
	table->pids = (int *)malloc(sizeof(int) * table->philos_len);
	if (table->print_sem == SEM_FAILED || table->meal_sem == SEM_FAILED
		|| table->dead_sem == SEM_FAILED || !table->pids)
	{
		clean_table(table);
		return (0);
	}
	return (1);
}
