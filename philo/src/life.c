/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:56:17 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/22 15:34:40 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destroy_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->total_philo)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	i = 0;
	while (i < table->total_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->philos);
	table->philos = NULL;
	free(table->forks);
	table->forks = NULL;
	pthread_mutex_destroy(&table->sim_mutex);
	pthread_mutex_destroy(&table->print_lock);
}

void	destroy_philos(t_table *table, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&table->philos[j].meal_mutex);
		j++;
	}
	free(table->philos);
	table->philos = NULL;
}

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}
