/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:57 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/09 16:11:58 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc > 4 && argc < 7)
	{
		if (validate_input_args(argv) == 0)
			return (EXIT_FAILURE);
		table.nbr_philos = ft_atoi(argv[1]);
		table.is_dead_flag = 0;
		if(!build_keys(&table) || !build_philos(&table, argv))
		{
			write(2, "Error building table\n", 21);
			return (EXIT_FAILURE);
		}
		init_table(&table);
	}
	else
	{
		write(2, "Invalid quantity of arguments\n", 30);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
