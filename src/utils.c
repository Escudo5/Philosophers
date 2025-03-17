/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:24:04 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/17 16:14:26 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int ft_error(int n)
{
    if (n == 1)
        printf("Número de argumentos inválido");
    if (n == 2)
        printf("Error al convertir argumentos");
    if (n == 3)
        printf("Error en argumentos\n");
    return(1);
}
int	ft_atoi(char *str)
{
	int i = 0;
	int sign;
	int result;
	while (str[i])
	{
		if ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
			str++;
		if (str[i] == '-')
			sign = -1;
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
		return (result * sign);
	}
}


int is_number(char *str)
{
    int i;
    i = 0;;
    if (!str || !str[0])
        return(0);
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            return(0);
        i++;
    }
    return(1);
}