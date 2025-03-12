/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:41:33 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/10 20:56:40 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_philo
{
	size_t			id;
	size_t			start_time;
	size_t			nbr_times_to_eat;
	size_t			meals_had;
	size_t			last_time_ate;
	pthread_t		philo_t;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	useconds_t		time_to_die;
	int				nbr_philos;
	int				is_eating;
	int				*a_dead_philo;
	int				dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*is_dead_key;
	pthread_mutex_t	*is_eating_key;
	pthread_mutex_t	*printing_key;
}	t_philo;

typedef struct s_table
{
	pthread_t		table_t;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_dead_key;
	pthread_mutex_t	is_eating_key;
	pthread_mutex_t	printing_key;
	int				nbr_philos;
	int				is_dead_flag;
}	t_table;

size_t	get_current_time(void);
void	*monitor(void *table_ptr);
void	*philo_routine(void *philo_ptr);
void	init_table(t_table *table);
void	print_msg(char *str, t_philo *philo);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		validate_input_args(char **args);
int		build_philos(t_table *table, char **args);
int		build_keys(t_table *table);
int		philos_alive(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
int		philo_eat(t_philo *philo);
void		improved_usleep(size_t millis, t_philo *philo);
void		clean(t_table *table);
