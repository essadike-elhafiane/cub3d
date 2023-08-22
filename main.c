/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:17:53 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/23 00:12:18 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void check_cub(char *name)
{   
    int len;
    char *str;

    len = ft_strlen(name);
    if (len < 5 || ft_strncmp(".cub", str = ft_substr(name, len - 4, 4), 4))
    {
        write(2, "Error map dos'nt have .cub \n", 28);
        free(str);
        exit(1);
    }
    free(str);
}

void     ft_free(char **map, char **only_map)
{
    int i;

    i = 0;
    while (map[i])
        free(map[i++]);
    free(map);
    i = 0;
    while (only_map[i])
        free(only_map[i++]);
    free(only_map);
}
void v()
{
    system("leaks cub");
}
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
    atexit(v);
    if (ac != 2)
        return (write(1, "Error in arg \n", 14 ), 1);
    check_cub(av[1]);
    fd = open(av[1], O_RDWR, 0777);
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
    if (!map[0])
        exit(1);
    if (check_map(map, &p, len))
        return (1);
    graphic(p.only_map, &p);
    ft_free(map, p.only_map);
    return (0);
}

// you don't check map.cub every file is work in your program