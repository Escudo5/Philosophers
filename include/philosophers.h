/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:25:29 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/14 16:43:56 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>


typedef struct s_table t_table;
typedef struct s_philo
{

    int id;  //id del filosofo
    int status; // estado, comiendo, pensando, durmiendo  1, 2, 0
    int left_fork;
    int right_fork;
    long long last_meal; // ultima vez que comio en ms
    t_table *table; // refrencia a la mesa
    pthread_mutex_t meal_lock; // mutex para proteger last meal
    pthread_t thread;  //creacion de hilos.

}t_philo;
typedef struct s_table
{

    int total_philo; 
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat; // veces que comer antes de terminar
    int sim_running;
    t_philo *philos; //array de filos
    pthread_mutex_t *forks; // array de mutex para tenedores
    pthread_mutex_t print_lock; // mmutex para proteher impresion
}t_table;

int ft_error(int n);
void philo_routine(void *philo);






#endif
