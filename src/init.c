/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:34:39 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/13 17:06:40 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <philosophers.h>

void philo_init(t_philo *philo, int id, t_table *table)
{    
    philo->id = id;
    philo->status = 2;
    philo->last_meal = get_time();
    philo->table;
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
    
    int fork_num;
    
    
    table->forks = pthread_mutex_init();
}