/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:06:25 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/07 14:58:52 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"


static char *get_action(int action)
{
    if (action == P_DIE)
        return("died.");
    if (action == P_FORK)
        return("has taken a fork.");
    if (action == P_EAT)
        return("is eating.");
    if (action == P_SLEEP)
        return("is sleepinig.");
    return("Error: not vaild msg id.");
}




void print_routine(t_philo *philo, int action)
{
    int t;
    t = get_time() - philo->table->start_time;
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->dead && !philo->table->full)
    {
        printf("%d %d %s \n", t, philo->id, get_action(action));

    }
    pthread_mutex_unlock(&philo->table->print_lock);
}