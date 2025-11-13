/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:18:55 by gekko             #+#    #+#             */
/*   Updated: 2025/11/13 18:25:13 by aelbouaz         ###   ########.fr       */
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

# define R "\033[31m" // Red
# define G "\033[32m" // Green
# define Y "\033[33m" // Yellow
# define B "\033[34m" // Blue
# define M "\033[35m" // Magenta
# define C "\033[36m" // Cyan
# define W "\033[37m" // White
# define BR "\033[1;31m" // Bold red
# define RESET "\033[0m"

typedef struct s_args	t_args;

typedef enum s_parity
{
	EVEN,
	ODD,
}	t_parity;

typedef enum s_status
{
	IDLE,
	SLEEPING,
	THINKING,
	TOOK_FIRST_FORK,
	TOOK_SECOND_FORK,
	EATING,
	DEAD,
}	t_status;

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_forks;

typedef struct s_philos
{
	t_args			*vars;
	long			id;
	long			priority;
	pthread_t		th;
	t_status		state;
	bool			full;
	long			meal_counter;
	long			last_meal;
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
	long			meals_eaten;
	long			threads_ready;
	long			death_occured;
	pthread_t		monitoring;
	t_forks			*forks;
	t_philos		*philos;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	monitor_mutex;
	long long		start_time;
	long long		*delta;
}	t_args;

int			error_handle(int argc, char **argv);
long		ft_atol(const char *str);
long long	get_time_in_ms(void);

void		*philo_routine(void *arg);
void		*monitoring_routine(void *arg);

int			initialise_vars_1(t_args *vars, int argc, char **argv);
int			initialise_vars_2(t_args *vars);
int			initialise_vars_3(t_args *vars);
int			initialise_threads(t_args *vars, void *(routine)(void *arg),
				void *(monitoring_routine)(void *arg));


void		start_mutexes(t_args *vars);
void		end_mutexes(t_args *vars);

void		cleanup(t_args *vars, int flag);
void		print_status(t_args vars);

void		philo_eat(t_philos *philo);
void		philo_sleep(t_philos *philo);
void		philo_think(t_philos *philo);

#endif
