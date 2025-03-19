/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:57 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/17 18:19:42 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	pre_delete_files(void)
{
	sem_unlink("/print");
	sem_unlink("/meal");
	sem_unlink("/dead");
	sem_unlink("/forks");
}

void	run_table(t_table *table)
{
	int			i;
	int			status;

	i = -1;
	while (++i < table->philos_len)
	{
		table->pids[i] = fork();
		if (table->pids[i] == 0)
			philo_process(i, table, &table->philos[i]);
	}
	i = -1;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) > 0)
			{
				while (++i < table->philos_len)
					kill(table->pids[i], SIGKILL);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc > 4 && argc < 7)
	{
		if (validate_input_args(argv) == 0)
			return (EXIT_FAILURE);
		if (!build_table(&table, argv))
			return (EXIT_FAILURE);
		if (!table.pids)
			exit(EXIT_FAILURE);
		pre_delete_files();
		if (!build_philos(&table, argv))
		{
			clean_table(&table);
			exit(EXIT_FAILURE);
		}
		run_table(&table);
		clean_table(&table);
	}
	else
	{
		write(2, "Invalid quantity of arguments\n", 30);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
