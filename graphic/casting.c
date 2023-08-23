/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:03:08 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/23 18:38:33 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// double	find_hr(t_data *data, double a_x, double a_y, double rotation)
// {
// 	while (1)
// 	{
// 		if (((rotation >= 0 && rotation <= M_PI)
// 				&& is_there_a_wall_1(a_x, a_y + 0.0001, data))
// 			|| is_there_a_wall_1(a_x, a_y, data))
// 		{
// 			break ;
// 		}
// 		if (rotation > 0 && rotation < M_PI)
// 		{
// 			a_y += TILE_SIZE;
// 			a_x += TILE_SIZE / tan(rotation);
// 		}
// 		else
// 		{
// 			a_y -= TILE_SIZE;
// 			a_x -= TILE_SIZE / tan(rotation);
// 		}
// 	}
// }

// double	find_vr(t_data *data, double a_x, double a_y, double rotation)
// {
// 	while (1)
// 	{
// 		if (((rotation > 3 * M_PI / 2 || rotation < M_PI / 2)
// 				&& is_there_a_wall_1(a_x + 0.0001, a_y, data))
// 			|| is_there_a_wall_1(a_x, a_y, data))
// 		{
// 			break ;
// 		}
// 		if (rotation > 3 * M_PI / 2 || rotation < M_PI / 2)
// 		{
// 			a_y += TILE_SIZE * tan(rotation);
// 			a_x += TILE_SIZE;
// 		}
// 		else
// 		{
// 			a_y -= TILE_SIZE * tan(rotation);
// 			a_x -= TILE_SIZE;
// 		}
// 	}
// }

double  dictance_horizontal(t_cub *y)
{
    double ystep = 32;
    double y_fisrt_interce;
	double x_fisrt_interce;

	double xstep = ystep / tan(y->angle_of_ray);
	if (y->angle_of_ray > 0 && y->angle_of_ray  < M_PI)
		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 + 32;
	else 
	{
		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 - 1e-8;
		ystep *= - 1;
		xstep *= - 1;
	}
	x_fisrt_interce = y->plr->x_p + ( y_fisrt_interce - y->plr->y_p ) / tan(y->angle_of_ray);
	while (x_fisrt_interce >= 0 && y_fisrt_interce >= 0 
		&& !check_wall_fram(x_fisrt_interce, y_fisrt_interce, y->map, y))
	{
			y_fisrt_interce += ystep;
			x_fisrt_interce += xstep;
	}
	return (y->hitwall_x = x_fisrt_interce, y->hitwall_y = y_fisrt_interce, distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce, y_fisrt_interce));
}

double  dictance_virtical(t_cub *y)
{
	double	x_fisrt_interce_v;
	double	y_fisrt_interce_v;
	double	xstep_v;
	double	ystep_v;
	
	xstep_v = 32;
	ystep_v = 32 * tan(y->angle_of_ray);
	if (y->angle_of_ray > 3 * M_PI / 2 || y->angle_of_ray < M_PI/2)
		x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 + 32;
	else
	{
		x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 - 1e-8;
		xstep_v *= -1;
		ystep_v *= -1;
	}
	y_fisrt_interce_v = y->plr->y_p + ((x_fisrt_interce_v - y->plr->x_p) * tan(y->angle_of_ray));
	while (x_fisrt_interce_v >= 0 && y_fisrt_interce_v >= 0 && !check_wall_fram(x_fisrt_interce_v, y_fisrt_interce_v, y->map, y))
	{
			y_fisrt_interce_v +=	ystep_v;
			x_fisrt_interce_v +=	xstep_v;
	}
	return (y->hitwall_x_v = x_fisrt_interce_v, y->hitwall_y_v = y_fisrt_interce_v, distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce_v, y_fisrt_interce_v));
}
// double  dictance_horizontal(t_cub *y)
// {
//     double ystep = 32;
//     double y_fisrt_interce;
// 	double x_fisrt_interce;

// 	double xstep = ystep / tan(y->angle_of_ray);
// 	if (y->angle_of_ray > 0 && y->angle_of_ray  < M_PI)
// 		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 + 32;
// 	else 
// 	{
// 		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 - 1e-8;
// 		ystep *= - 1;
// 		xstep *= - 1;
// 	}
// 	printf("\n\n%f | %f\n\n", xstep, ystep);
// 	printf("%f | %f", y_fisrt_interce, x_fisrt_interce);
// 	// exit(1);
// 	x_fisrt_interce = y->plr->x_p + ( y_fisrt_interce - y->plr->y_p ) / tan(y->angle_of_ray);
// 	while (x_fisrt_interce >= 0 && x_fisrt_interce < 2000
// 		&& y_fisrt_interce >= 0 && y_fisrt_interce < 1000
// 		&& !check_wall_fram(x_fisrt_interce, y_fisrt_interce, y->map, y))
// 	{
// 			y_fisrt_interce += ystep;
// 			x_fisrt_interce += xstep;
// 			// printf("sdgsgdsgsgd\n");
// 			// printf("%f | %f", y_fisrt_interce, x_fisrt_interce);
// 			// if (x_fisrt_interce > 100000 || y_fisrt_interce > 100000)
// 			// 	exit(1);
// 	}
// 	return (y->hitwall_x = x_fisrt_interce, y->hitwall_y = y_fisrt_interce, distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce, y_fisrt_interce));
// }

// double  dictance_virtical(t_cub *y)
// {
// 	double	x_fisrt_interce_v;
// 	double	y_fisrt_interce_v;
// 	double	xstep_v;
// 	double	ystep_v;
	
// 	xstep_v = 32;
// 	ystep_v = 32 * tan(y->angle_of_ray);
// 	if (y->angle_of_ray > 3 * M_PI || 2 && y->angle_of_ray < M_PI/2)
// 		x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 + 32;
// 	else
// 	{
// 		x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 - 1e-8;
// 		xstep_v *= -1;
// 		ystep_v *= -1;
// 	}
// 	// printf("\n\n%f | \n\n", ystep_v);
// 	y_fisrt_interce_v = y->plr->y_p + ((x_fisrt_interce_v - y->plr->x_p) * tan(y->angle_of_ray));
// 	while (x_fisrt_interce_v >= 0 && x_fisrt_interce_v < 2000 && y_fisrt_interce_v >= 0
// 		&& y_fisrt_interce_v < 1000 && !check_wall_fram(x_fisrt_interce_v, y_fisrt_interce_v, y->map, y))
// 	{
// 			y_fisrt_interce_v +=	ystep_v;
// 			x_fisrt_interce_v +=	xstep_v;
// 			// printf("%f | %f", y_fisrt_interce_v, x_fisrt_interce_v);
// 			// if (x_fisrt_interce_v > 100000 || y_fisrt_interce_v > 100000)
// 			// 	exit(1);
// 	}
// 	return (y->hitwall_x_v = x_fisrt_interce_v, y->hitwall_y_v = y_fisrt_interce_v, distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce_v, y_fisrt_interce_v));
// }
