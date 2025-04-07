/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:56 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/07 14:59:16 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void philo_eat(t_philo *philo)
{
    if (philo->table->dead)
        return;
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_routine(philo, P_FORK);
    // pthread_mutex_lock(&philo->table->print_lock);
    // printf("Philosopher %d ha cogido tenedor izquierdo\n", philo->id);
    // pthread_mutex_unlock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_routine(philo, P_FORK);
    // pthread_mutex_lock(&philo->table->print_lock);
    // //printf("Philosopher %d ha cogido tenedor derecho\n", philo->id);
    // pthread_mutex_unlock(&philo->table->print_lock);
    philo->status = 1; 
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->meal_mutex);
    if (philo->table->dead)
    {
        pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
        return;
    }
    //printf("Philo %d comiendo\n", philo->id);
    print_routine(philo, P_EAT);
    usleep(philo->table->time_to_eat * 1000);
    if(!philo->table->dead)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        printf("Philosopher %d ha soltado ambos tenedores\n", philo->id);
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
        // pthread_mutex_lock(&philo->table->print_lock);
        //printf("Philo %d durmiendo\n", philo->id);
        philo->status = 0;
        //pthread_mutex_unlock(&philo->table->print_lock);
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
        //pthread_mutex_lock(&philo->table->print_lock);
        //printf("Philo %d pensando\n", philo->id);
        philo->status = 2;
        //pthread_mutex_unlock(&philo->table->print_lock);
        usleep(10);
    }
}

void *philo_routine(void *philo)
{
    t_philo *ph = (t_philo *)philo;
    printf("Hilo iniciado -> ID: %d, Dirección: %p\n", ph->id, (void*)ph);
    printf("Simulación iniciada, sim_running = %d\n", ph->table->sim_running);
    //usleep(1000 - ph->id * 10);
    if (ph->id % 2 != 0)
        usleep(1000);
    while (ph->table->dead == 0)  
    {
        //printf("Filósofo %d ha terminado su rutina\n", ph->id);

        //funcion de javi comprobacion hilos
        // pthread_mutex_lock(&ph->table->sim_mutex);
        // if (ph->table->sim_running == 0)
        // {
        //     pthread_mutex_unlock(&ph->table->sim_mutex);
        //     break;
        // }
        // pthread_mutex_unlock(&ph->table->sim_mutex);
        //printf("funcion comer\n");
        philo_eat(ph);
        philo_sleep(ph);
        //printf("Entro en funcion pensar\n");
        philo_think(ph);
    }
    return(NULL);
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
        printf("Simulación detenida por muerte del filósofo %d\n", philo->id);
        pthread_mutex_unlock(&philo->table->sim_mutex);
        print_routine(philo, P_DIE);
        // pthread_mutex_lock(&philo->table->print_lock);
        // printf("Filosofo %d died", philo->id);
        // pthread_mutex_unlock(&philo->table->print_lock);
        alive = 0;
    }  
    pthread_mutex_unlock(&philo->meal_mutex);
    return(alive);
}
