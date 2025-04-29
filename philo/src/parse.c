/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:19 by smarquez          #+#    #+#             */
/*   Updated: 2025/04/29 10:02:22 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	assign_value(int *dst, char *str)
{
	long	tmp;

	tmp = ft_atol(str);
	if (tmp > INT_MAX || tmp <= 0)
		return (1);
	*dst = (int)tmp;
	return (0);
}

int	parse(t_table *table, int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	i = 1;
	while (i < argc)
		if (!is_number(argv[i++]))
			return (ft_error(2));
	if (assign_value(&table->total_philo, argv[1])
		|| assign_value(&table->time_to_die, argv[2])
		|| assign_value(&table->time_to_eat, argv[3])
		|| assign_value(&table->time_to_sleep, argv[4]))
		return (ft_error(3));
	if (argc == 6)
	{
		if (assign_value(&table->max_meals, argv[5]))
			return (ft_error(3));
	}
	else
		table->max_meals = -1;
	return (0);
}
