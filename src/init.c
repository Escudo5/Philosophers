/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:34:39 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/17 16:51:03 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"

void philo_init(t_philo *philo, int id, t_table *table)
{    
    philo->id = id;
    philo->status = 2;
    philo->last_meal = get_time();
    philo->table = table;
    philo->left_fork = id - 1;
    philo->right_fork = id % table->total_philo;
    pthread_mutex_init(&philo->meal_mutex, NULL);
}

void init_all_philos(t_table *table)
{
    int i;
    i = 0;
    while (i < table->total_philo)
    {
        philo_init(&table->philos[i], i + 1, table);
        i++;
    }
}


void init_forks(t_table *table)
{ 
    int i;
    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * (table->total_philo));
    while (i < table->total_philo)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
}

void destroy_forks(t_table *table)
{
    int i;
    i = 0;
    while (i < table->total_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
    table->forks = NULL;
}


void start_threads(t_table *table)
{
    int i;
    i = 0;
    while (i < table->total_philo)
    {
        pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]);
        i++;
    }
    pthread_create(&table->monitor, NULL, monitor_philos, &table);
}