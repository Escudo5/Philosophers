/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:56:17 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/25 11:49:32 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


// void *philo_routine(void *philo)
// {
//    t_philo *ph = (t_philo *)philo;

//    while (1)
//    {
//       pthread_mutex_lock(&ph->table->sim_mutex);  
//       if (ph->table->sim_running == 0)  
//       {
//          pthread_mutex_unlock(&ph->table->sim_mutex);  
//          break;  
//       }
//       pthread_mutex_unlock(&ph->table->sim_mutex);  
//       if (get_time() - ph->last_meal >= ph->table->time_to_die)
//          break;
//       pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
//       pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
//       pthread_mutex_lock(&ph->table->print_lock);
//       printf("Ha cogido 2 tenedores \n");
//       pthread_mutex_unlock(&ph->table->print_lock);
//       ph->status = 1;
//       pthread_mutex_lock(&ph->meal_mutex);
//       ph->last_meal = get_time();
//       pthread_mutex_unlock(&ph->meal_mutex);

//       pthread_mutex_lock(&ph->table->print_lock);
//       printf("comiendo");
//       pthread_mutex_unlock(&ph->table->print_lock);
//       usleep(ph->table->time_to_eat * 1000);
//       pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
//       pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
//       ph->status = 0;
//       pthread_mutex_lock(&ph->table->print_lock);
//       printf("durmiendo");
//       pthread_mutex_unlock(&ph->table->print_lock);
//       usleep(ph->table->time_to_sleep * 1000);
//       ph->status = 2;
//       pthread_mutex_lock(&ph->table->print_lock);
//       printf("pensando");
//       pthread_mutex_unlock(&ph->table->print_lock);
//       usleep(1000);
//    }
//    return(NULL);
// }


//se podria quitar el print de linea 24 para ahorrar lineas.


void *monitor_philos(void *arg)
{
   t_table *table = (t_table *)arg;
   int i;
   printf("ENtro en la funcion monitor\n");
   while (1)
   {
      i = 0;
      while (i < table->total_philo)
      {
         printf("Verificando filo %d -> Direccion: %p\n", i, (void *)&table->philos[i]);
         printf("Filo %d -> meal_mutex en %p\n", i, (void *)&table->philos[i].meal_mutex);
         pthread_mutex_lock(&table->philos[i].meal_mutex); //da segfault a partir de aqui
         if (get_time() - table->philos[i].last_meal > table->time_to_die)
         {
            pthread_mutex_unlock(&table->philos[i].meal_mutex);
            pthread_mutex_lock(&table->sim_mutex); 
            table->sim_running = 0; 
            pthread_mutex_unlock(&table->sim_mutex); 
            pthread_mutex_lock(&table->print_lock);
            printf("Filósofo %d ha muerto\n", i);
            pthread_mutex_unlock(&table->print_lock);
             
         }
         pthread_mutex_unlock(&table->philos[i].meal_mutex);
         i++;
      }
      usleep(1000); 
   }
      printf("salgo de funcion monitor\n");
}

void destroy_all(t_table *table)
{
   int i;
   i = 0;
   while (i < table->total_philo)
   {
      pthread_mutex_destroy(&table->philos[i].meal_mutex);
      i++;
   }
   i = 0;
   while(i < table->total_philo)
   {
      pthread_mutex_destroy(&table->forks[i]);
      i++;
   }
   pthread_mutex_destroy(&table->sim_mutex);
   pthread_mutex_destroy(&table->print_lock);
}

