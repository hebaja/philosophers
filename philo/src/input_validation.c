/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:33 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/09 16:11:45 by hebatist         ###   ########.fr       */
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

unsigned int	ft_atoui(const char *str)
{
	unsigned int	res;

	res = 0;
	if (*str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\v'
			|| *str == '\r' || *str == '\n' || *str == '\f')
			str++;
		if (*str == '+' || *str == '-')
			str++;
		while (*str >= '0' && *str <= '9')
		{
			res = res * 10 + (*str - 48);
			str++;
		}
	}
	return (res);
}

int	is_valid_args(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	is_out_bounds(char *str)
{
	unsigned int	nbr;

	nbr = ft_atoui(str);
	if (nbr > 2147483647)
		return (1);
	return (0);
}

int	validate_input_args(char **args)
{
	int	flag;

	flag = 0;
	if (ft_atoi(args[1]) <= 0 || !is_valid_args(args[1])
		|| is_out_bounds(args[1]))
		write(2, "Invalid number of philosophers\n", 31);
	else if (ft_atoi(args[2]) <= 0 || !is_valid_args(args[2])
		|| is_out_bounds(args[1]))
		write(2, "Invalid time to die\n", 20);
	else if (ft_atoi(args[3]) <= 0 || !is_valid_args(args[3])
			|| is_out_bounds(args[1]))
		write(2, "Invalid time to eat\n", 20);
	else if (ft_atoi(args[4]) <= 0 || !is_valid_args(args[4])
			|| is_out_bounds(args[1]))
		write(2, "Invalid time to sleep\n", 22);
	else if (args[5] && (ft_atoi(args[5]) <= 0 || !is_valid_args(args[5])
			|| is_out_bounds(args[1])))
		write(2, "Invalid number of times philosophers must eat\n", 46);
	else
		flag = 1;
	return (flag);
}
