/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:56 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/14 12:16:26 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void philo_eat(t_philo *philo)
{
    if (philo->table->dead)
        return;
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_routine(philo, P_FORK);
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_routine(philo, P_FORK);
    philo->status = 1; 
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    if (philo->table->dead)
    {
        pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
        return;
    }
    print_routine(philo, P_EAT);
    usleep(philo->table->time_to_eat * 1000);
    if(!philo->table->dead)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        pthread_mutex_unlock(&philo->table->print_lock);
    }
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void philo_sleep(t_philo *philo)
{
    long sleep_start;
    sleep_start = get_time();
    if (philo->table->dead)
        return;
    if (philo->status != 0)
    {
        print_routine(philo, P_SLEEP);
        philo->status = 0;
    }
    while (get_time() - sleep_start < philo->table->time_to_sleep)
    {
        if (philo->table->dead)
            return;
        usleep(100);
    }
}

void philo_think(t_philo *philo)
{
    if (philo->table->dead)
        return;
    if (philo->status != 2)
    {
        print_routine(philo, P_THINK);
        philo->status = 2;
        usleep(10);
    }
}

void *philo_routine(void *philo)
{
    t_philo *ph = (t_philo *)philo;
    pthread_mutex_lock(&ph->table->monitor);
    pthread_mutex_unlock(&ph->table->monitor);
    if (ph->id % 2 != 0)
        usleep(1000);
    while (ph->table->dead == 0 && (ph->table->max_meals == -1 || ph->meals_eaten < ph->table->max_meals))
    {
        if (ph->table->dead)
            break;
        philo_eat(ph);
        philo_sleep(ph);
        philo_think(ph);
    }
    pthread_mutex_lock(&ph->table->meal_full);
    ph->table->full++;
    pthread_mutex_unlock(&ph->table->meal_full);
    return(NULL);
}
int is_alive(t_philo *philo)
{
    int alive;
    alive = 1;
    pthread_mutex_lock(&philo->meal_mutex);
    if (philo->table->full)
    {
        pthread_mutex_unlock(&philo->meal_mutex);
        return(1);
    }
    if (get_time() - philo->last_meal >= philo->table->time_to_die)
    {
        pthread_mutex_lock(&philo->table->sim_mutex);
        if (philo->table->dead == 0)
        {
            philo->table->dead = 1;
            print_routine(philo, P_DIE);
        }
        pthread_mutex_unlock(&philo->table->sim_mutex);
        alive = 0;
    }
    pthread_mutex_unlock(&philo->meal_mutex);
    return(alive);
}
