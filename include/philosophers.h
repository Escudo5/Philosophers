/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:25:29 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/09 16:10:25 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>



enum e_action
{
    P_EAT,
    P_SLEEP,
    P_THINK,
    P_FORK,
    P_DIE,
};

typedef struct s_table t_table;
typedef struct s_philo
{

    int id;  //id del filosofo
    int status; // estado, comiendo, pensando, durmiendo  1, 2, 0
    int left_fork;
    int right_fork;
    int meals_eaten;
    long long last_meal; // ultima vez que comio en ms
    t_table *table; // refrencia a la mesa
    pthread_mutex_t meal_mutex; // mutex para proteger last meal
    pthread_t thread;  //creacion de hilos.

}t_philo;

typedef struct s_table
{

    int dead;

    int total_philo; 
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat; // veces que comer antes de terminar
    int sim_running;
    int max_meals;
    int sim_start;
    int start_time;
    int full;
    t_philo *philos; //array de filos
    pthread_mutex_t sim_mutex;
    pthread_mutex_t *forks; // array de mutex para tenedores
    pthread_mutex_t print_lock; // mmutex para proteher impresion
    pthread_mutex_t monitor; 
}t_table;


long long get_time(void);


int ft_error(int n);
void init_forks(t_table *table);
void init_all_philos(t_table *table);
void philo_init(t_philo *philo, int id, t_table *table);
void destroy_forks(t_table *table);
void start_threads(t_table *table);
void destroy_all(t_table *table);
void *philo_routine(void *philo);
void *monitor_philos(void *philo);
int	ft_atoi(char *str);
int is_number(char *str);
long long get_time(void);
void *dummy_routine(void *arg);
int is_alive(t_philo *philo);
int parse(t_table *table, int argc, char **argv);
void print_routine(t_philo *philo, int action);









#endif
