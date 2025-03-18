/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:56 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/18 16:36:07 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void philo_eat(t_philo *philo)
{
    if (get_time() - philo->last_meal >= philo->table->time_to_die)
        return;
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->meal_mutex);

    pthread_mutex_lock(&philo->left_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d ha cogido tenedor izq\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);

    pthread_mutex_lock(&philo->right_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d ha cogido tenedor dcho\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);

    philo->status = 1; 

    usleep(philo->table->time_to_eat * 1000); 

    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(&philo->right_fork);
}

void philo_sleep(t_philo *philo)
{
    if (get_time() - philo->last_meal >= philo->table->time_to_die)
        return;
    if (philo->status == 1)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        philo->status = 0;
        printf("Philo durmiendo\n");
        pthread_mutex_unlock(&philo->table->print_lock);
        usleep(philo->table->time_to_sleep * 1000);
    }
}

void philo_think(t_philo *philo)
{
    if (get_time() - philo->last_meal >= philo->table->time_to_die)
        return;
    if (philo->status == 0)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        philo->status = 2;
        printf("Philo pensando\n");
        pthread_mutex_unlock(&philo->table->print_lock);
    }
}