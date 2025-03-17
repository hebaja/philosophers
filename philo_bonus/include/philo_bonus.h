/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:41:33 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/12 21:52:40 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_fork
{
	size_t	id;
	char	*sem_name;
	sem_t	*sem;
}	t_fork;

typedef struct s_philo
{
	size_t			id;
	size_t			start_time;
	size_t			times_to_eat_len;
	size_t			meals_had;
	size_t			last_time_meal;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	useconds_t		time_to_die;
	int				philos_len;
	int				is_eating;
	int				is_sleeping;
	int				dead;
	int				*dead_flag;
}	t_philo;

typedef struct s_table
{
	int				*pids;
	int				philos_len;
	int				dead_flag;
	char			*print_sem_name;
	char			*meal_sem_name;
	char			*dead_sem_name;
	sem_t			*print_sem;
	sem_t			*meal_sem;
	sem_t			*dead_sem;
	size_t			start_time;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

size_t	get_current_time(void);
void	*monitor(void *table_ptr);
void	*philo_routine(void *philo_ptr);
void	init_table(t_table *table);
void	print_msg(char *str, t_table *table, t_philo *philo);
void	improved_usleep(size_t millis, t_table *table, t_philo *philo);
void	clean(t_table *table);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		validate_input_args(char **args);
// int		build_philos(t_table *table, char **args);
// int		build_keys(t_table *table);
// int		philos_alive(t_philo *philo);
// int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
int		philo_eat(t_philo *philo);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_itoa(int n);

#endif
