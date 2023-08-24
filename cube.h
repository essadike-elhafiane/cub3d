/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:18:49 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/23 23:29:35 by eelhafia         ###   ########.fr       */
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

typedef struct s_path
{
	int p;
	int cc;
	int f[3];
	int c[3];
	int ff;
	int flg;
	int fd;
    int len;
    int i;
	char *no;
	char *so;
	char *we;
	char *ea;
	char **only_map;
}t_path;

typedef struct s_cube
{
	void			*img;
	int				with_map;
	double			distancee;
	int				hight_map;
	char			**map;
	void			*mlx;
	mlx_texture_t	*img_data_n;
	mlx_texture_t	*img_data_e;
	mlx_texture_t	*img_data_s;
	mlx_texture_t	*img_data_w;
	uint8_t			*data_pixel;
	mlx_image_t		*imgg;
	mlx_image_t		*img_n;
	mlx_image_t		*img_s;
	mlx_image_t		*img_w;
	mlx_image_t		*img_e;
	int				h;
	double			hitwall_x_v;
	double			hitwall_y_v;
	double			hitwall_x;
	double			hitwall_y;
	double			angle_of_ray;
	t_player		*plr;
	t_path			*path;
} t_cub;


int		check_map(char **map , t_path *p, int len);
void    graphic(char **map_only, t_path *p);
double	dictance_horizontal(t_cub *y);
void	check_line(char *map_line);
void	render_next_frame(t_cub *y);
int		check_wall_fram(double x, double y, char **map, t_cub *data);
double	distance_p(double x, double y, double x1, double y1);
double  dictance_virtical(t_cub *y);
void	randerwall(t_cub *y, int m);
void	draw_player(t_cub *y);

#endif
