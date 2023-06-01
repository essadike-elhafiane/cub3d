/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:28:26 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/01 16:43:14 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void check_line(char *map_line)
{
    int i;
    int flg;

    flg = 1;
    i = 0;
    while (map_line[i])
    {
        while (map_line[i] == ' ')
            i++;
        if (map_line[i++] == '1')
            flg = 0;
        if (map_line[i] == '0')
            flg = 1;
        while (map_line[i] == '0')
            i++;
        
        
    }
    
}