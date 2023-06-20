/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:33:28 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/20 21:06:20 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

//for convert a degrees to rad 

double deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

static mlx_image_t* image;

int check_direction(char c)
{
	if (c == 'S' || c == 'E' || c == 'W' || c == 'N')
		return (1);
	return (0);
}


// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_pixel(int x, int y, unsigned int color)
{
	int i = 0;
	
	while (i < 32)
	{
		int j = 0;
		while (j < 32)
		{
			mlx_put_pixel(image, (y * 32) + i , (x * 32) + j, color);
			// mlx_put_pixel(image, (y * 32) , (x * 32), 0x0FFFFF);

			j++;
		}
		// mlx_put_pixel(image, (y * 32) + i , (x * 32), 0x0FFFFF);
		i++;
	}
}

void draw_line(t_cub *data, double dis, double rotation)
{
	double end_x = data->plr->x_p + dis * cos(rotation);
	double end_y = data->plr->y_p + dis * sin(rotation);

	int x0 = data->plr->x_p;
	int y0 = data->plr->y_p;
	int x1 = (int)end_x;
	int y1 = (int)end_y;
	
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	
	while (1) {
	    mlx_put_pixel(image, x0, y0, 0x00FF0000);
		if ((x0 == x1) && (y0 == y1))
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) 
		{
			err += dx;
			y0 += sy;
		}
	}	
}

int check_is_wall(double y, double x, t_cub *data)
{
	// if (y >= 100 || x >= 100)
	// 	return 1;
	int idy  = y / 32;
	int idx = x / 32;
	int idy1  = (y + 1) / 32;
	int idy_1  = (y - 1) / 32;
	int idx1 = (x + 1) / 32;
	if (y < 0)
		return (1);
	if (x < 0)
		return (1);
	// printf("x == %d | y == %d | c == %c \n", idx, idy, data->map[idy + 9][idx + 1]);
	if (data->map[idy][idx] && (data->map[idy][idx] == '1' || data->map[idy][idx1] == '1' \
	|| data->map[idy1][idx] == '1' || data->map[idy_1][idx] == '1'))
		return 1;
	// if (!map[idy + 9][idx + 1] || map[idy + 9][idx + 1] == '1')
	// 	return (1);
	return (0);
}


double distance_p(double x, double y, double x1, double y1)
{
	return(sqrt(((x1-x) * (x1-x)) + ((y1-y) * (y1 - y))));
}
int angle = 60;

int check_wall_fram(double x, double y, char **map, t_cub *data)
{
	int xx = (int)floor(x / 32);
	int xx1 = (int)floor((x + 1) / 32);
	int xx_1 = (int)floor((x - 1) / 32);
	int yy = (int)floor(y / 32);
	int yy_1 = (int)floor((y - 1 )/ 32);
	int yy1 = (int)floor((y + 1) / 32);
	// int yy = (int)floor(y / 32);
	if (yy < 0 || yy >= data->hight_map)
		return (1);
	if (xx < 0 || xx >= ft_strlen(map[yy]))
		return (1);
	if (map[yy][xx] == '1' || map[yy][xx1] == '1' || map[yy][xx_1] == '1' || map[yy1][xx] == '1' || map[yy_1][xx] == '1')
		return (1);
	return (0);
}

void frame_playr(void *f)
{
	t_cub *y = f;
	int j = 0;
	int i = 0;
	while (i < 1)
	{
		j = 0;
		while (j < 1)
		{
			mlx_put_pixel(image, y->plr->x_p + i , j + y->plr->y_p , 0xFFFF00);
			j++;
		}
		i++;
	}

	// i = 0;
	// while (i < 4)
	// {
	// 	j = 0;
	// 	while (j < 4)
	// 	{
	// 		mlx_put_pixel(image, y->plr->a_x + i ,  j + y->plr->a_y , 0xFF3333);
	// 		j++;
	// 	}
	// 	i++;
	// }
	
	// first intersections horizontal 
	
	// double y_fisrt_interce = floor(y->plr->y_p / 32) * 32;
	

	// steep horizontal // 
	
	// vertical intersections










	
	// int flgg = 0;
	// float x_fisrt_interce_v = 0;
	// float y_fisrt_interce_v = 0;

	// if (y->plr->derction >  3 * M_PI / 2 ||  y->plr->derction  <  M_PI / 2)
	// {
	// 	x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 + 32;
	// 	flg = 1;
	// // 	// x_fisrt_interce = y->plr->x_p + (y->plr->y_p - y_fisrt_interce) / tan(y->plr->derction);
	// }
	// else 
	// 	x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 - 1;
	


	
	
	// y_fisrt_interce_v = y->plr->y_p + ((x_fisrt_interce - y->plr->x_p) * tan(y->plr->derction)) - 1;
	// // double xstep_v = 32;
	// // double ystep_v = xstep_v * tan(y->plr->derction);
	
	// // // if (!flg)
	// // // {
	// // // 	ystep_v *= -1;
	// // // 	xstep_v *= -1;
	// // // }
	// while (x_fisrt_interce_v >= 0 && x_fisrt_interce_v < 2000
	// 	&& y_fisrt_interce_v >= 0 && y_fisrt_interce_v < 1000 && !check_wall_fram(x_fisrt_interce_v, y_fisrt_interce_v, y->map))
	// {
	// 	if (flg)
	// 	{
	// 		y_fisrt_interce_v +=	32 * tan(y->plr->derction);
	// 		x_fisrt_interce_v +=	32;
	// 	}
	// 	else
	// 	{
	// 		y_fisrt_interce_v -=	32 * tan(y->plr->derction);
	// 		x_fisrt_interce_v -=	32; 
	// 	}
	// }
	// while (x_fisrt_interce > 0 && y_fisrt_interce > 0 && x_fisrt_interce <  2000
	// 	&& y_fisrt_interce < 1000 && !check_wall_fram(y_fisrt_interce_v, x_fisrt_interce_v, y->map))
	// {
	// 	y_fisrt_interce_v += ystep_v;
	// 	x_fisrt_interce_v += xstep_v;
	// }


	int m = 0;
	double dictence_h = 0;
	double dictence_v = 0;

	y->angle_of_ray = y->plr->derction - (deg2rad(30));
	while (m < 2000)
	{
		dictence_h = dictance_horizontal(y);
		dictence_v = dictance_virtical(y);
		if (dictence_h < dictence_v)
			{
				draw_line(y, dictence_h, y->angle_of_ray);
				y->distancee = dictence_h;
			}
		else
			{
				draw_line(y, dictence_v, y->angle_of_ray);
				y->distancee = dictence_v;
			}
		randerwall(y, m);
		y->angle_of_ray += deg2rad(60) / 2000;
		m++;
	}
	
	// draw_line(y,  100, y->plr->derction - r * 2);
	// draw_line(y,  100, y->plr->derction - r);
	// draw_line(y,  100, y->plr->derction + r);
	// draw_line(y,  100, y->plr->derction + r * 2);
	// draw_line(y,  100, y->plr->derction + r * 3);
	// draw_line(y,  100, y->plr->derction + r * 4);
	// draw_line(y,  100, y->plr->derction + r * 5);
	// draw_line(y,  100, y->plr->derction + r * 6);
	// draw_line(y,  100, y->plr->derction + r * 7);
	// draw_line(y,  100, y->plr->derction + r * 8);
	// draw_line(y,  100, y->plr->derction + r * 9);
	// draw_line(y,  100, y->plr->derction + r * 10);
	// draw_line(y,  100, y->plr->derction + r * 11);
}

void	randerwall(t_cub *y, int m)
{
	int i;
	// static int yy;
	
	i = 0;
	int height_of_wall = 20000 / y->distancee;
	int top = (1000 / 2) - (height_of_wall / 2);
	int down = (1000 / 2) + (height_of_wall / 2);
	top = top < 0 ? 0 : top;
	down = down > 1000 ? 1000 : down;
	while (top < down)
	{
		mlx_put_pixel(image, m, top, 0xFFFFFF0);
		top++;
	}
}

void ft_hook1(void* param)
{
	t_cub* y = param;

	if (mlx_is_key_down(y->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(y->mlx);
	if (mlx_is_key_down(y->mlx, MLX_KEY_UP))
	{
		if (!check_is_wall(y->plr->y_p + 2 * sin(y->plr->derction), y->plr->x_p + 2 * cos(y->plr->derction), y))
		{
			y->plr->y_p += 2 *sin(y->plr->derction);
			y->plr->x_p += 2 *cos(y->plr->derction);
		}
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_DOWN))
	{
		if (!check_is_wall(y->plr->y_p - 2 * sin(y->plr->derction), y->plr->x_p - 2 * cos(y->plr->derction), y))
		{
			y->plr->y_p -= 2 *sin(y->plr->derction);
			y->plr->x_p -= 2 *cos(y->plr->derction);
		}
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_LEFT))
	{
		y->plr->derction -= 2 * M_PI / 180;
		if (y->plr->derction < 0)
				y->plr->derction = (2 * M_PI) + y->plr->derction;
		
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_RIGHT))
	{
		y->plr->derction += 2 * M_PI / 180;
		if (y->plr->derction  >= 2 * M_PI)
				y->plr->derction  = 0;
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	mlx_delete_image(y->mlx, image);
	image = mlx_new_image(y->mlx, 2000, 1000);
	render_next_frame(y);
	frame_playr(y);
	mlx_image_to_window(y->mlx, image, 0, 0);
}


void render_next_frame(t_cub *y)
{
	int i = 0;
	while (y->map[i])
	{
		int j = 0;
		while (y->map[i][j])
		{
			if (y->map[i][j] == '0' || check_direction(y->map[i][j]))
				draw_pixel(i, j, 0xFFFFFF0);
			if (y->map[i][j] == '1')
				draw_pixel(i, j, 0x000FF);
			j++;
		}
		i++;
	}
}

int ft_strlen_pnt(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

double init_direction(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (-M_PI / 2);
	if (c == 'W')
		return (M_PI);
	if (c == 'S')
		return (M_PI / 2);
	return (-1);
}

void    graphic(char **map, char **map_only)
{
    t_cub y;
    y.map = map_only;
	
	y.plr = malloc(sizeof(t_player));
	y.with_map = ft_strlen(map[9]);
	y.hight_map = ft_strlen_pnt(map_only);
	printf("%d is with || %d is height\n", y.with_map, y.hight_map);
    y.mlx = mlx_init(2000, 1000, "cube3D", false);

   	image = mlx_new_image(y.mlx, 2000, 1000);
	int i = 0;
	while (y.map[i])
	{
		int j = 0;
		while (y.map[i][j])
		{
			if (y.map[i][j] == '1')
				draw_pixel(i, j, 0xFFFFFFF);
			if (check_direction(y.map[i][j]))
			{
				y.plr->x_p = j * 32;
				y.plr->y_p = i * 32;
				y.plr->derction = init_direction(y.map[i][j]);
				y.plr->a_x = y.plr->x_p + 20 * cos(y.plr->derction);
				y.plr->a_y = y.plr->y_p + 20 * sin(y.plr->derction);
			}
			j++;
		}
		i++;
	}
	// render_next_frame(&y);
	// mlx_loop_hook(y.mlx, ft_randomize, &y);
	mlx_loop_hook(y.mlx, ft_hook1, &y);
	mlx_image_to_window(y.mlx, image, 0, 0);
	mlx_loop(y.mlx);
}

// when we want to calcul a dictance between a and b just we need to transfer it to trangle Ay - By = ab and Ax - Bx = Ac and we will calclut auther line with tng or sin or cos 