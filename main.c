/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:17:53 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/19 19:18:27 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// void mlx_mini_map(char **map)
// {
//    void *mlx;
//    void *win;
//    void *mini_im;
   
//    mlx = mlx_init();
//    win = mlx_new_window(mlx , 640, 480 ,"minimap");
//    mini_im =  mlx_new_image(mlx,50,50);
   
//     mlx_loop(mlx);    
// }


int main(int ac, char **av)
{
    int fd;
    int len;
    int i;
    char *str;
    char **map;
    char **only_map;
    
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
    // if (check_map(map))
    //     return (1);
         
    only_map = (char **) malloc(sizeof(char *) * (i - 8 + 1));
    int j = 8;
    int a = 0;
    while (map[j])
    {
        only_map[a++] = ft_strdup(map[j++]);
    }
    // j = 0;
    // while (only_map[j])
    // {
    //     printf("%s", only_map[j++]);
    // }
    
    graphic(map, only_map);
    // mlx_mini_map(map);
    // i = 0;
    // while (map[i])
    //     printf("%s", map[i++]);
    // printf("%s", map[i]);
    
}

//  your parsing dosn't check the last line in map you should be handle this 
// should be handle fist caracter in every line in your map, mast be 1 