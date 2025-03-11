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

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	if (*str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\v'
			|| *str == '\r' || *str == '\n' || *str == '\f')
			str++;
		if (*str == '+' || *str == '-')
		{
			if (*str == '-')
				sign = -1;
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			res = res * 10 + (*str - 48);
			str++;
		}
	}
	return (res * sign);
}

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
		if (*philo->is_dead)
			break ;
		usleep(500);
	}
}

void	print_msg(char *str, t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->printing_key);
	printf("%lu %lu %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->printing_key);
}
