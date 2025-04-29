/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:31:53 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/29 10:03:18 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_first_fork(t_philo *philo, int first_fork)
{
	if (!is_dead(philo->table))
		pthread_mutex_lock(&philo->table->forks[first_fork]);
	else
		return (1);
	if (!is_dead(philo->table))
		print_routine(philo, P_FORK);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return (1);
	}
	if (philo->table->total_philo == 1)
	{
		while (1)
		{
			if (is_dead(philo->table))
			{
				pthread_mutex_unlock(&philo->table->forks[first_fork]);
				return (1);
			}
			usleep(1000);
		}
	}
	return (0);
}

int	take_second_fork(t_philo *philo, int first_fork, int second_fork)
{
	if (!is_dead(philo->table))
		pthread_mutex_lock(&philo->table->forks[second_fork]);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return (1);
	}
	if (!is_dead(philo->table))
		print_routine(philo, P_FORK);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[second_fork]);
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return (1);
	}
	return (0);
}

int	is_dead(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->sim_mutex);
	dead = table->dead;
	pthread_mutex_unlock(&table->sim_mutex);
	return (dead);
}
