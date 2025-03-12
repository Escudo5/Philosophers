/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:24:04 by smarquez          #+#    #+#             */
/*   Updated: 2025/03/12 16:27:30 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_error(int n)
{
    if (n == 1)
        printf("Número de argumentos inválido");
    if (n == 2)
        printf("Error al convertir argumentos");


    return(1);
}