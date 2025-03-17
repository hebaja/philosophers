/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:57 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/09 20:31:14 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void	clean_forks(t_fork *forks, int forks_len)
{
	int	i;

	i = -1;
	while (++i < forks_len)
	{
		sem_close(forks[i].sem);
		sem_unlink(forks[i].sem_name);
		free(forks[i].sem_name);
	}
}

void	clean_table(t_table *table)
{
	sem_close(table->print_sem);
	sem_close(table->meal_sem);
	sem_close(table->dead_sem);
	sem_unlink(table->print_sem_name);
	sem_unlink(table->meal_sem_name);
	sem_unlink(table->dead_sem_name);
	if (table->pids)
		free(table->pids);
	if (table->forks)
		clean_forks(table->forks, table->philos_len);
	if (table->philos)
		free(table->philos);
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	printf("%lu %lu %s\n", time, philo->id, str);
}

void	pre_delete_files(int len)
{
	int		i;
	char	*end;
	char	*name;

	i = -1;
	sem_unlink("/print");
	sem_unlink("/meal");
	sem_unlink("/dead");	
	while (++i < len)
	{
		end = ft_itoa(i);
		name = ft_strjoin("/fork", ft_itoa(i));
		sem_unlink(name);
		free(end);
		free(name);
	}
}

int	build_forks(t_table *table)
{
	int		i;
	char	*end;
	t_fork	*forks;

	i = -1;
	pre_delete_files(table->philos_len);
	forks = (t_fork *)malloc(sizeof(t_fork) * table->philos_len);
	if (!forks)
		return(0);
	while (++i < table->philos_len)
	{
		end = ft_itoa(i);
		forks[i].id = i + 1;
		forks[i].sem_name = ft_strjoin("/fork", ft_itoa(i));
		forks[i].sem = sem_open(forks[i].sem_name, O_CREAT | O_EXCL, 0664, 1);
		if (!forks[i].sem)
		{
			clean_forks(forks, i);
			free(end);
			free(table->pids);
			return (0);
		}
		free(end);
	}
	table->forks = forks;
	return (1);
}

int	philo_is_dead(t_table *table, t_philo *philo)
{
	size_t	current_time;

	sem_wait(table->meal_sem);
	// sem_wait(table->dead_sem);
	current_time = get_current_time();
	if (current_time - philo->last_time_meal
		>= philo->time_to_die && philo->is_eating == 0)
	{
		if (table->dead_flag)
			return (0);
		sem_wait(table->dead_sem);
		table->dead_flag = 1;
		sem_post(table->dead_sem);
		print_msg("died", table, philo);
		// sem_post(table->dead_sem);
		sem_post(table->meal_sem);
		return (1);
	}
	// sem_post(table->dead_sem);
	sem_post(table->meal_sem);
	return (0);
}

// int	philos_alive(t_table *table, t_philo *philo)
// {
// 	int	res;

// 	res = 1;
// 	sem_wait(table->dead_sem);
// 	if (*philo->dead_flag)
// 		res = 0;
// 	sem_post(table->dead_sem);
// 	return (res);
// }

// int	philo_sleep(t_table *table, t_philo *philo)
// {
// 	if (!philos_alive(table, philo))
// 		return (0);
// 	print_msg("is sleeping", table, philo);
// 	improved_usleep(philo->time_to_sleep, table, philo);
// 	return (1);
// }


int	build_philo_procs(int i, t_table *table, t_philo *philo)
{
	sem_t	*fork_l;
	sem_t	*fork_r;

	if (i % 2 == 0)
		usleep(1000);

	while (1)
	{

		if (philo_is_dead(table, philo) || table->dead_flag)
			exit(EXIT_FAILURE);

		if (philo->times_to_eat_len != 0 && (philo->meals_had == philo->times_to_eat_len))
			break ;
		fork_l = table->forks[i].sem;
		if (i == 0)
			fork_r = table->forks[table->philos_len - 1].sem;
		else
			fork_r = table->forks[i - 1].sem;
		
		sem_wait(fork_l);

		if (philo_is_dead(table, philo) || table->dead_flag)
		{
			sem_post(fork_l);
			exit(EXIT_FAILURE);
		}

		print_msg("took a fork", table, philo);
		if (table->philos_len == 1)
		{
			improved_usleep(philo->time_to_die, table, philo);
			philo->dead = 1;
			*philo->dead_flag = 1;
			exit(EXIT_FAILURE);
		}

		sem_wait(fork_r);
		
		if (philo_is_dead(table, philo) || table->dead_flag)
		{
			sem_post(fork_l);
			sem_post(fork_r);
			exit(EXIT_FAILURE);
		}

		print_msg("took a fork", table, philo);
		philo->is_eating = 1;
		// print_msg("is eating", table, philo);
		print_message("is eating", philo);
		sem_wait(table->meal_sem);
		philo->meals_had++;
		philo->last_time_meal = get_current_time();
		sem_post(table->meal_sem);
		improved_usleep(philo->time_to_eat, table, philo);
		sem_post(fork_l);
		sem_post(fork_r);
		philo->is_eating = 0;


		// if (!philo_sleep(table, philo))
		// 	exit(EXIT_FAILURE);
		if (table->dead_flag)
			exit(EXIT_FAILURE);
		// philo->is_sleeping = 1;
		print_message("is sleeping", philo);
		improved_usleep(philo->time_to_sleep, table, philo);
		// print_msg("is sleeping", table, philo);
		// philo->is_sleeping = 0;
		// if (table->dead_flag)
		// 	exit(EXIT_FAILURE);
		// print_msg("is thinking", table, philo);
		print_message("is thinking", philo);
	}
	exit(EXIT_SUCCESS);
}

int	build_philos(t_table *table, char **args)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * table->philos_len);
	if (!philos)
		return (0);
	philos->dead_flag = &table->dead_flag;
	while(++i < table->philos_len)
	{
		philos[i].id = i + 1;
		philos[i].philos_len = table->philos_len;
		philos[i].dead = 0;
		philos[i].is_eating = 0;
		philos[i].is_sleeping = 0;
		philos[i].meals_had = 0;
		philos[i].start_time = table->start_time;
		philos[i].last_time_meal = get_current_time();
		philos[i].time_to_die = ft_atoi(args[2]);
		philos[i].time_to_eat = ft_atoi(args[3]);
		philos[i].time_to_sleep = ft_atoi(args[4]);
		if (args[5])
			philos[i].times_to_eat_len = ft_atoi(args[5]);
		else
			philos[i].times_to_eat_len = 0;
	}
	table->philos = philos;
	return (1);
}

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;
	int			status;
	int			pid;
	pthread_t	table_monitor;

	if (argc > 4 && argc < 7)
	{
		if (validate_input_args(argv) == 0)
			return (EXIT_FAILURE);
		table.dead_flag = 0;
		table.philos_len = ft_atoi(argv[1]);
		table.start_time = get_current_time();
		table.print_sem_name = "/print";
		table.meal_sem_name = "/meal";
		table.dead_sem_name = "/dead";	
		table.print_sem = sem_open(table.print_sem_name, O_CREAT | O_EXCL, 0644, 1);
		table.meal_sem = sem_open(table.meal_sem_name, O_CREAT | O_EXCL, 0644, 1);
		table.dead_sem = sem_open(table.dead_sem_name, O_CREAT | O_EXCL, 0644, 1);
		table.pids = (int *)malloc(sizeof(int) * table.philos_len);
		if (!table.pids)
			exit(EXIT_FAILURE);
		if(!build_forks(&table) || !build_philos(&table, argv))
		{
			clean_table(&table);
			exit(EXIT_FAILURE);
		}
		
		i = -1;
		while (++i < table.philos_len)
		{
			table.pids[i] = fork();
			if (table.pids[i] == 0)
				build_philo_procs(i, &table, &table.philos[i]);
		}

		while ((pid = waitpid(-1, &status, 0)) > 0)
		{
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) > 0)
				{
					table.dead_flag = 1;
					printf("%d broken\n", WEXITSTATUS(status));
					i = -1;
					while (++i < table.philos_len)
					{
						kill(table.pids[i], SIGKILL);
					}
					while (wait(NULL) > 0);
					exit(EXIT_FAILURE);
				}
			}
		}
		clean_table(&table);
	}
	else
	{
		write(2, "Invalid quantity of arguments\n", 30);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
