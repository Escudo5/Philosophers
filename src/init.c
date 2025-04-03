/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:34:39 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/03 15:10:10 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"

void philo_init(t_philo *philo, int id, t_table *table)
{    
    table->dead = 0;

    philo->id = id;
    philo->status = 1;
    philo->last_meal = get_time();
    philo->table = table;
    philo->table->sim_running = 1;
    philo->left_fork = id - 1;
    philo->right_fork = id % table->total_philo;
    pthread_mutex_init(&philo->meal_mutex, NULL);
}

void init_all_philos(t_table *table)
{
    int i;
    i = 0;
    if (table->total_philo <= 0 || table->total_philo > 200)
    {
        printf("Error en el numero de filos\n");
        return;
    }
    table->philos = malloc(sizeof(t_philo) * table->total_philo);
    if (!table->philos)
    {
        printf("Error: no memoria para filo\n");
        return;
    }
    printf("malloc philos en %p\n", (void *)table->philos);
    while (i < table->total_philo)
    {
        if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0)
        {
            printf("Error: no se puede init_all\n");
            free(table->philos);
            table->philos = NULL;
            return;
        }
        philo_init(&table->philos[i], i + 1, table);
        // printf("cre los hilos para cada filo\n, %d", table->philos[i].id);
        i++;
    }
}


void init_forks(t_table *table)
{ 
    int i;
    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * (table->total_philo));
    if (!table->forks)
    {
        printf("No memoria para tenedores\n");
        return;
    }
    // printf("malloc tenedores\n");
    while (i < table->total_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
        {
            printf("error no mutex\n");
            free(table->forks);
            table->forks = NULL;
            return;
        }
        i++;
    }
    //if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0) //rompe aqui, parece que no crea bien filo[i]
        //printf("Error: no se pudo iniciar mutex\n");

}

void destroy_forks(t_table *table)
{
    int i;
    i = 0;
    while (i < table->total_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
    table->forks = NULL;
}


void start_threads(t_table *table)
{
    int	i;

	i = 0;
	while (i < table->total_philo)
	{
        printf("Creando hilo %d -> Dirección: %p, ID: %d, Left fork: %d, Right fork: %d\n",
       i, (void*)&table->philos[i], table->philos[i].id,
       table->philos[i].left_fork, table->philos[i].right_fork);


        printf("Inicio hilo \n %d", i);
		int err = pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]);
        if (err != 0)
            printf("Error creando el hilo %d: %s\n", i, strerror(err));
		i++;
	}
    
    // if (pthread_create(&table->monitor, NULL, &philo_routine, table) != 0)
    // {
    //     printf("no se puede crear monitor\n");
    //     return;
    // }
    pthread_mutex_init(&table->print_lock, NULL);
    pthread_mutex_init(&table->sim_mutex, NULL);
    printf("todos hilos creados\n");
}
