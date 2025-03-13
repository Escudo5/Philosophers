/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:34:39 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/13 16:01:50 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <philosophers.h>

void philo_init(t_philo *philo, int id)
{    
    philo->id = id;    
}

void init_all_philos(t_table *table)
{
    int i;
    i = 0;
    while (i < table->total_philo)
    {
        philo_init(&table->philos[i], i + 1);
        i++;
    }
}
