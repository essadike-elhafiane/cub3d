/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:33:28 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/19 00:56:38 by eelhafia         ###   ########.fr       */
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
			mlx_put_pixel(image, (y * 32) , (x * 32), 0x0FFFFF);

			j++;
		}
		mlx_put_pixel(image, (y * 32) + i , (x * 32), 0x0FFFFF);
		i++;
	}
}

void draw_line(t_cub *data, double dis, double rotation)
{
	double end_x = data->plr->x_p + 32 + dis * cos(rotation);
	double end_y = data->plr->y_p + 32 + dis * sin(rotation);

	int x0 = data->plr->x_p + 32;
	int y0 = data->plr->y_p + 32;
	int x1 = (int)end_x;
	int y1 = (int)end_y;
	
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	
	while (1) {
	    mlx_put_pixel(image, x0, y0, 0x00FF0099);
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
	if (y >= 1000 || x >= 2000)
		return 1;
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
	if (data->map[idy + 9][idx + 1] && (data->map[idy + 9][idx + 1] == '1' || data->map[idy + 9][idx1 + 1] == '1' \
	|| data->map[idy1 + 9][idx + 1] == '1' || data->map[idy_1 + 9][idx + 1] == '1'))
		return 1;
	// if (!map[idy + 9][idx + 1] || map[idy + 9][idx + 1] == '1')
	// 	return (1);
	return (0);
}


double distance_p(double x, double y, double x1, double y1)
{
	return(sqrt(((x1-x) * (x1-x)) + ((y1-y) * (y1 - y))));
}

int check_wall_fram(double x, double y, char **map)
{
	int xx = (int)floor(x / 32);
	int yy = (int)floor(y / 32);
	if (map[yy + 9][xx] == '1')
		return (1);
	return (0);
}

void frame_playr(void *f)
{
	t_cub *y = f;
	int j = 0;
	int i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(image, y->plr->x_p + 32  + i , 32 + j + y->plr->y_p , 0xFFFF00);
			j++;
		}
		i++;
	}

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(image, y->plr->a_x + 32  + i , 32 + j + y->plr->a_y , 0xFF3333);
			j++;
		}
		i++;
	}
	
	// double r = M_PI / 180;
	// double rayangle = y->plr->derction - (60 / 2);
	// // horizontal intersections
	// int norm_angle = rayangle % (2 * M_PI);
	
	// conerte PI to positif number //
	if (y->plr->derction < 0)
		y->plr->derction = (2 * M_PI) + y->plr->derction;
	if (y->plr->derction  >= 2 * M_PI)
			y->plr->derction  = 0;
	// y->plr->derction = norm_angle;
	
	// first intersections horizontal 
	double y_fisrt_interce = floor(y->plr->y_p / 32) * 32;
	

	// steep horizontal // 
	double ystep = 32;
	double xstep = ystep / tan(y->plr->derction);
	int flg = 0;
	
	// DOwn
	if (y->plr->derction > 0 && y->plr->derction  < M_PI)
	{
		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 + 32;
		flg = 1;
		// x_fisrt_interce = y->plr->x_p + (y->plr->y_p - y_fisrt_interce) / tan(y->plr->derction);
	}
	// up
	else 
		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 - 1;
	
	double x_fisrt_interce = y->plr->x_p + ( y_fisrt_interce - y->plr->y_p ) / tan(y->plr->derction);
	// if (y->plr->derction > M_PI && y->plr->derction  <  2 * M_PI)
	// {
	// 	y_fisrt_interce = floor(y->plr->y_p / 32) * 32;
	// 	ystep *= -1;
	// }
	
	if (!flg)
	{
		ystep *= -1;
		xstep *= -1;
	}
		// left
	
	while (x_fisrt_interce >= 0 && x_fisrt_interce < 2000 && y_fisrt_interce >= 0 && y_fisrt_interce < 1000 && !check_wall_fram(x_fisrt_interce, y_fisrt_interce, y->map))
	{
	// right
		y_fisrt_interce += ystep;
		x_fisrt_interce += xstep;
	}
	double dictence_h = distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce, y_fisrt_interce);
	// vertical intersections










	
	// flg = 0;
	// double x_fisrt_interce_v;

	// if (y->plr->derction >=  3 * M_PI / 2 ||  y->plr->derction  <=  M_PI / 2)
	// {
	// 	x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 + 32;
	// 	flg = 1;
	// // 	// x_fisrt_interce = y->plr->x_p + (y->plr->y_p - y_fisrt_interce) / tan(y->plr->derction);
	// }
	// else 
	// 	x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32;
	


	
	
	// double y_fisrt_interce_v = y->plr->y_p + (x_fisrt_interce - y->plr->x_p) * tan(y->plr->derction) - 1;
	
	// double xstep_v = 32;
	// double ystep_v = xstep_v * tan(y->plr->derction);
	
	// if (!flg)
	// {
	// 	ystep_v *= -1;
	// 	xstep_v *= -1;
	// }
	// while (x_fisrt_interce > 0 && y_fisrt_interce > 0 && x_fisrt_interce <  2000
	// 	&& y_fisrt_interce < 1000 && !check_is_wall(y_fisrt_interce_v, x_fisrt_interce_v, y))
	// {
	// 	y_fisrt_interce_v += ystep_v;
	// 	x_fisrt_interce_v += xstep_v;
	// }


	int c = 0;
	float	a_x = 0;
	float	a_y = 0;

	if (y->plr->derction > 3*M_PI/2 || y->plr->derction < M_PI/2)
	{
		a_x = floor(y->plr->x_p / 32) * 32;
		c = 1;
	}
	else
		a_x = floor(y->plr->x_p / 32) * 32;
	printf("rad : %f  x = %f y = %f\n", y->plr->derction, a_x, a_y);
	
	a_y = y->plr->y_p + ((a_x - y->plr->x_p) * tan(y->plr->derction)) - 1;
	while (a_x >= 0 && a_x < 2000 && a_y >= 0 && a_y < 1000 && !check_wall_fram(a_x, a_y, y->map))
	{
		if (c)
		{
			a_y +=	32 * tan(y->plr->derction);
			a_x +=	32;
		}
		else
		{
			a_y -=	32 * tan(y->plr->derction);
			a_x -=	32; 
		}
	}
	
	double dictence_v = distance_p(y->plr->x_p, y->plr->y_p, a_x, a_y);
	
	if (dictence_h < dictence_v)
		draw_line(y, dictence_h, y->plr->derction);
	else
	{
		if (c)
			draw_line(y, dictence_v - 32, y->plr->derction);
		else
			draw_line(y, dictence_v + 1, y->plr->derction);
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
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_RIGHT))
	{
		y->plr->derction += 2 * M_PI / 180;
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
	while (y->map[i + 8])
	{
		int j = 0;
		while (y->map[i + 8][j])
		{
			if (y->map[i + 8][j] == '0' || check_direction(y->map[i + 8][j]))
				draw_pixel(i, j, 0xFFFFFF0);
			if (y->map[i + 8][j] == '1')
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

void    graphic(char **map)
{
    t_cub y;
    y.map = map;
	
	y.plr = malloc(sizeof(t_player));
	y.with_map = ft_strlen(map[17]);
	y.hight_map = ft_strlen_pnt(map);
	y.hight_map -= 8;
	printf("%d is with || %d is height\n", y.with_map, y.hight_map);
    y.mlx = mlx_init(2000, 1000, "cube3D", false);

   	image = mlx_new_image(y.mlx, 2000, 1000);
	int i = 0;
	while (y.map[i + 8])
	{
		int j = 0;
		while (y.map[i + 8][j])
		{
			if (y.map[i + 8][j] == '1')
				draw_pixel(i, j, 0xFFFFFFF);
			if (check_direction(y.map[i + 8][j]))
			{
				y.plr->x_p = j * 32;
				y.plr->y_p = i * 32;
				y.plr->derction = init_direction(y.map[i + 8][j]);
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