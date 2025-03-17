/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:18 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/17 17:35:35 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		perror("gettimeofday() error");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	improved_usleep(size_t millis, t_table *table)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < millis)
	{
		if (table->dead_flag)
			break ;
		usleep(500);
	}
}

void	print_msg(char *str, t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	printf("%lu %lu %s\n", time, philo->id, str);
}

void	print_dead_msg(char *str, t_table *table, t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	sem_wait(table->print_sem);
	if (table->dead_flag)
		usleep(1000);
	printf("%lu %lu %s\n", time, philo->id, str);
	sem_post(table->print_sem);
}
