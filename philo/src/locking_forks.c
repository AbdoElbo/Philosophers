/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:22:04 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/12/09 21:07:51 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	lock_forks(t_philos *philo)
{
	int	first;
	int	second;

	first = philo->right_fork->fork_id;
	second = philo->left_fork->fork_id;
	if (first < second)
		lock_right_fork_first(philo);
	else
		lock_left_fork_first(philo);
}

void	lock_right_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	print_status(philo, "has taken a fork", G);
	pthread_mutex_lock(&philo->left_fork->fork);
	print_status(philo, "has taken a fork", G);
}

void	lock_left_fork_first(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	print_status(philo, "has taken a fork", G);
	pthread_mutex_lock(&philo->right_fork->fork);
	print_status(philo, "has taken a fork", G);
}
