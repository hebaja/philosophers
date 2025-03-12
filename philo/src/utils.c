/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:18 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/10 20:57:20 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	improved_usleep(size_t millis, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < millis)
	{
		if (*philo->a_dead_philo)
			break ;
		usleep(500);
	}
}

void	print_msg(char *str, t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->printing_key);
	pthread_mutex_lock(philo->is_dead_key);
	printf("%lu %lu %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->is_dead_key);
	pthread_mutex_unlock(philo->printing_key);

}
