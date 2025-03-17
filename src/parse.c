/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:19 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/17 16:13:54 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int parse(t_table *table, int argc, char **argv)
{
    int i;
    i = 1;
    if (argc != 5 && argc != 6)
        return(ft_error(1));
    while (i < argc)
    {
        if (!is_number(argv[i]))
            return(ft_error(2));
        i++;
    }
    table->total_philo = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        table->max_meals = ft_atoi(argv[5]);
    else 
        table->max_meals = -1;
    if (table->total_philo <= 0 || table->time_to_die <= 0 || table->time_to_eat <= 0 || table->time_to_sleep <= 0 || (argc == 6 && table->max_meals <= 0))
        return(ft_error(3));
}
