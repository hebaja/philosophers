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

int	validate_input_args(char **args)
{
	int	flag;

	flag = 0;
	if (ft_atoi(args[1]) <= 0 || !is_valid_args(args[1]))
		write(2, "Invalid number of philosophers\n", 31);
	else if (ft_atoi(args[2]) <= 0 || !is_valid_args(args[2]))
		write(2, "Invalid time do die\n", 20);
	else if (ft_atoi(args[3]) <= 0 || !is_valid_args(args[3]))
		write(2, "Invalid time do eat\n", 20);
	else if (ft_atoi(args[4]) <= 0 || !is_valid_args(args[4]))
		write(2, "Invalid time do sleep\n", 22);
	else if (args[5] && (ft_atoi(args[5]) <= 0 || !is_valid_args(args[5])))
		write(2, "Invalid number of times philosophers must eat\n", 46);
	else
		flag = 1;
	return (flag);
}
