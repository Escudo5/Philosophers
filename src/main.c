/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:07 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/14 17:30:24 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void *monitor_routine(void* arg)
{
    t_table *table = (t_table*)arg;
    int i;
    while (1)
    {
        i = 0;
        while (i < table->total_philo)
        {
            if (!is_alive(&table->philos[i]))
                return(NULL);
            i++;
        }
        pthread_mutex_lock(&table->meal_full);
        if (table->full == table->total_philo)
        {
            pthread_mutex_unlock(&table->meal_full);
            return(NULL);
        }
        pthread_mutex_unlock(&table->meal_full);
        usleep(500);
    }
    return(NULL);
}
int main(int argc, char **argv)
{
    t_table table;
    table = (t_table){0};
    if (parse(&table, argc, argv) != 0)
        return(1);
    table.start_time = get_time();
    init_all_philos(&table);
    init_forks(&table);
    start_threads(&table);
    pthread_create(&table.monitor_thread, NULL, monitor_routine, &table);
    int i;
    i = 0;
    while (i < table.total_philo)
    {
        pthread_join(table.philos[i].thread, NULL);
        i++;
    }
    pthread_join(table.monitor_thread, NULL);
    destroy_all(&table);
    return(0);
}
