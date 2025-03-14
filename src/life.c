/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:56:17 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/14 16:46:16 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void philo_routine(void *philo)
{
   t_philo *ph = (t_philo *)philo;
   while (get_time() - ph->last_meal < ph->table->time_to_die && ph->table->sim_running)
   {
        pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
        pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
        ph->status = 1;
        ph->last_meal = get_time();
        usleep(ph->table->time_to_eat * 1000);
        pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
        pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
   }
}
