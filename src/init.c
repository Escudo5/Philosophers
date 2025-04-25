/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:34:39 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/25 12:21:29 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_init(t_philo *philo, int id, t_table *table)
{
	table->dead = 0;
	philo->id = id;
	philo->status = 1;
	philo->last_meal = get_time();
	philo->table = table;
	philo->table->full = 0;
	philo->left_fork = id - 1;
	philo->right_fork = id % table->total_philo;
}

int	init_all_philos(t_table *table)
{
	int	i;

	i = 0;
	if (table->total_philo <= 0 || table->total_philo > 200)
	{
		return (ft_error(3));
	}
	table->philos = calloc(sizeof(t_philo), table->total_philo);
	if (!table->philos)
	{
		return (ft_error(2));
	}
	while (i < table->total_philo)
	{
		if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0)
		{
			table->philos = NULL;
			return (ft_error(2));
		}
		philo_init(&table->philos[i], i + 1, table);
		i++;
	}
	return (0);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = calloc(sizeof(pthread_mutex_t), (table->total_philo));
	if (!table->forks)
	{
		printf("No memoria para tenedores\n");
		return ;
	}
	while (i < table->total_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			printf("error no mutex\n");
			destroy_forks(table, i);
			table->forks = NULL;
			return ;
		}
		i++;
	}
}

void	destroy_forks(t_table *table, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&table->forks[j]);
		j++;
	}
	free(table->forks);
	table->forks = NULL;
}

void	start_threads(t_table *table)
{
	int	i;
	int	err;

	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->sim_mutex, NULL);
	pthread_mutex_init(&table->monitor, NULL);
	pthread_mutex_init(&table->meal_full, NULL);
	i = 0;
	while (i < table->total_philo)
	{
		err = pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]);
		if (err != 0)
			printf("Error creando el hilo %d: %s\n", i, strerror(err));
		i++;
	}
}
