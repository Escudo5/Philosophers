/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:31:53 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/25 12:21:09 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_first_fork(t_philo *philo, int first_fork)
{
	if (!philo->table->dead)
		pthread_mutex_lock(&philo->table->forks[first_fork]);
	else
		return ;
	if (!philo->table->dead)
		print_routine(philo, P_FORK);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return ;
	}
	if (philo->table->total_philo == 1)
	{
		while (1)
		{
			if (philo->table->dead)
			{
				pthread_mutex_unlock(&philo->table->forks[first_fork]);
				return ;
			}
			usleep(1000);
		}
	}
}

void	take_second_fork(t_philo *philo, int first_fork, int second_fork)
{
	if (!philo->table->dead)
		pthread_mutex_lock(&philo->table->forks[second_fork]);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return ;
	}
	if (!philo->table->dead)
		print_routine(philo, P_FORK);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[second_fork]);
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return ;
	}
}
