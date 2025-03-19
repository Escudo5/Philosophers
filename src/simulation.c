/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:56 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/19 14:23:57 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void philo_eat(t_philo *philo)
{
    if (!is_alive(philo))
        return;
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d ha cogido tenedor izq\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d ha cogido tenedor dcho\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    philo->status = 1; 
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->meal_mutex);
    if (!is_alive(philo))
    {
        pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
        return;
    }
    usleep(philo->table->time_to_eat * 1000); 
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d ha soltado ambos tenedores\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void philo_sleep(t_philo *philo)
{
    long sleep_start;
    sleep_start = get_time();
    if (!is_alive(philo))
        return;
    if (philo->status != 0)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        printf("Philo  %ddurmiendo\n", philo->id);
        philo->status = 0;
        pthread_mutex_unlock(&philo->table->print_lock);
    }
    while (get_time() - sleep_start < philo->table->time_to_sleep)
    {
        if (!is_alive(philo))
            return;
        usleep(1000);
    }
}

void philo_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->sim_mutex);
    if (philo->table->sim_running == 0)
    {
        pthread_mutex_unlock(&philo->table->sim_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->table->sim_mutex);

    if (philo->status == 0)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        philo->status = 2;
        printf("Philo pensando\n");
        pthread_mutex_unlock(&philo->table->print_lock);
        usleep(1000 *   100);
    }
}

void philo_routine(t_philo *philo)
{
    while (1)  
    {
        pthread_mutex_lock(&philo->table->sim_mutex);
        if (philo->table->sim_running == 0)
        {
            pthread_mutex_unlock(&philo->table->sim_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->table->sim_mutex);
        if (philo->id % 2 != 0)
            usleep(philo->table->time_to_eat * 500);
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
}
int is_alive(t_philo *philo)
{
    int alive;
    alive = 1;
    pthread_mutex_lock(&philo->meal_mutex);
    if (get_time() - philo->last_meal >= philo->table->time_to_die)
    {
        pthread_mutex_lock(&philo->table->sim_mutex);
        philo->table->sim_running = 0;
        pthread_mutex_unlock(&philo->table->sim_mutex);
        pthread_mutex_lock(&philo->table->print_lock);
        printf("Filosofo %d ha muerto.", philo->id);
        pthread_mutex_unlock(&philo->table->print_lock);
        alive = 0;
    }  
    pthread_mutex_unlock(&philo->meal_mutex);
    return(alive);
}

// void sleep()
// {
//     if (is_alive(philo))
//     {
//         while (tiempo de usleep < sleep_time)
//         codigo de funcion sleep dividida en varios intervalos
//         otra comprobacion de is is_alive
        
//     }
// }