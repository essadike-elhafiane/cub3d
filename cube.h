/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:18:49 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/19 21:34:35 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "/Users/eelhafia/Desktop/MLX42/include/MLX42/MLX42.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

typedef struct s_player
{
	double	x_p;
	double	y_p;
	double	a_x;
	double	a_y;
	double	derction;
} t_player;

typedef struct s_cube
{
	void	*img;
	int		with_map;
	int		hight_map;
	char	**map;
	void	*mlx;
	double	angle_of_ray;
	t_player *plr;
}t_cub;

int		check_map(char **map);
void    graphic(char **map, char **map_only);
double	dictance_horizontal(t_cub *y);
void	check_line(char *map_line);
void	render_next_frame(t_cub *y);
int		check_wall_fram(double x, double y, char **map, t_cub *data);
double	distance_p(double x, double y, double x1, double y1);
double  dictance_virtical(t_cub *y);

#endif
