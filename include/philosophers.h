/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:25:29 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/15 17:00:27 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

enum					e_action
{
	P_EAT,
	P_SLEEP,
	P_THINK,
	P_FORK,
	P_DIE,
};

typedef struct s_table	t_table;
typedef struct s_philo
{
	int					id;
	int					status;
	int					left_fork;
	int					right_fork;
	int					meals_eaten;
	long long			last_meal;
	t_table				*table;
	pthread_mutex_t		meal_mutex;
	pthread_t			thread;

}						t_philo;

typedef struct s_table
{
	int					dead;
	int					total_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	int					start_time;
	int					full;
	t_philo				*philos;
	pthread_mutex_t		sim_mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		monitor;
	pthread_mutex_t		meal_full;
	pthread_t			monitor_thread;
}						t_table;

long long				get_time(void);

int						ft_error(int n);
void					init_forks(t_table *table);
int					init_all_philos(t_table *table);
void					philo_init(t_philo *philo, int id, t_table *table);
void					destroy_philos(t_table *table, int i);
void					destroy_forks(t_table *table, int i);
void					start_threads(t_table *table);
void					destroy_all(t_table *table);
void					*philo_routine(void *philo);
void					*monitor_philos(void *philo);
int						ft_atoi(char *str);
int						is_number(char *str);
long long				get_time(void);
void					*dummy_routine(void *arg);
int						is_alive(t_philo *philo);
int						parse(t_table *table, int argc, char **argv);
void					print_routine(t_philo *philo, int action);
void					*ft_memset(void *s, int c, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					update_meal(t_philo *philo);

#endif
