/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:18:55 by gekko             #+#    #+#             */
/*   Updated: 2025/11/24 14:06:01 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"
# define R "\033[1;31m"
# define RESET "\033[0m"

typedef struct s_args	t_args;

typedef enum s_parity
{
	EVEN,
	ODD,
}	t_parity;

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_forks;

typedef struct s_philos
{
	t_args			*vars;
	long			id;
	pthread_t		th;
	long			full;
	long			meal_counter;
	long long		last_meal;
	t_forks			*right_fork;
	t_forks			*left_fork;
	t_parity		parity;
}	t_philos;

typedef struct s_args
{
	long			philos_num;
	long			forks_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_to_eat;
	long			threads_ready;
	long			death_occured;
	long			sim_end;
	pthread_t		monitoring;
	t_forks			*forks;
	t_philos		*philos;
	pthread_mutex_t	printf_mtx;
	pthread_mutex_t	philo_mtx;
	pthread_mutex_t	monitor_mtx;
	pthread_mutex_t	set_read_mtx;
	pthread_mutex_t	time_mtx;
	long long		start_time;
	int				cleanup_flag;
}	t_args;

int			error_handle(int argc, char **argv);
long		ft_atol(const char *str);
long long	get_time_in_ms(void);
void		start_mutexes(t_args *vars);
void		end_mutexes(t_args *vars);
void		cleanup(t_args *vars);

long		get_long(pthread_mutex_t *mutex, long *dst);
void		set_long(pthread_mutex_t *mutex, long *dst, long updated);
long long	get_long_long(pthread_mutex_t *mutex, long long *dst);
void		set_long_long(pthread_mutex_t *mutex, long long *dst,
				long long updated);

int			initialise_vars_1(t_args *vars, int argc, char **argv);
int			initialise_vars_2(t_args *vars);
int			initialise_threads(t_args *vars, void *(routine)(void *arg),
				void *(monitoring_routine)(void *arg));

void		*philo_routine(void *arg);
void		*monitoring_routine(void *arg);

void		philo_eat(t_philos *philo);
void		philo_sleep(t_philos *philo);
void		philo_think(t_philos *philo);

#endif
