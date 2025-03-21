/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:07 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/20 17:34:34 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int main(int argc, char **argv)
{
    t_table table;
    if (argc != 5 && argc != 6)
        return(ft_error(1));
    long time =get_time();
    printf("%ld\n", time);
    table.total_philo = ft_atoi(argv[1]);
    table.time_to_die = ft_atoi(argv[2]);
    table.time_to_eat = ft_atoi(argv[3]);
    table.time_to_sleep = ft_atoi(argv[4]);
    init_all_philos(&table);
    printf("Entro en fincion de hilos\n");
    init_forks(&table);
    start_threads(&table);
    // int i;
    // i = 0;
    // while (i < table.total_philo)
    // {
    //     pthread_join(table.philos[i].thread, NULL);
    //     i++;
    // }
    // printf("Llega al join despues del while\n");
    // pthread_join(table.monitor, NULL); //el codigo rompe  aqui
    // printf("Salgo del join\n");
    // destroy_all(&table);
    return(0);
}

    // if (argc == 6)
    //     table.max_meals = ft_atoi(argv[5]);
    // else
    //     table.max_meals = -1;
    // printf("Filósofos: %d, Tiempo de muerte: %d, Tiempo de comer: %d, Tiempo de dormir: %d, Comidas máximas: %d\n",table.total_philo, table.time_to_die, table.time_to_eat, table.time_to_sleep, table.max_meals);