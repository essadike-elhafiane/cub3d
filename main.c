/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:17:53 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/20 17:05:59 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int ac, char **av)
{
    int fd;
    int len;
    int i;
    char *str;
    char **map;
    t_path p;

    p.ea = NULL;
    p.we = NULL;
    p.no = NULL;
    p.so = NULL;
    p.ff = 0;
    p.cc = 0;
    len = 0;
    i = 0;
    if (ac > 2)
        return (write(1, "Error in arg \n", 14 ), 1);
    fd = open(av[1], O_RDONLY, 0777);
    if (fd < 0)
        return (write(2, "Error open file\n", 16), 1);
    while (1)
    {
        str = get_next_line(fd);
        if (!str)
            break;
        free(str);
        len++;
    }
    map = (char **) malloc(sizeof(char *) * (len + 1));
    close(fd);
    fd = open(av[1], O_RDONLY, 0777);
    while (i <= len)
        map[i++] = get_next_line(fd); 
    if (check_map(map, &p, len))
        return (1);
    graphic(p.only_map, &p);
}

//  your parsing dosn't check the last line in map you should be handle this 
// should be handle fist caracter in every line in your map, mast be 1 