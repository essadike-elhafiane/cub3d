/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:03:08 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/21 20:44:31 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 - 0.01;
		ystep *= - 1;
		xstep *= - 1;
	}
	x_fisrt_interce = y->plr->x_p + ( y_fisrt_interce - y->plr->y_p ) / tan(y->angle_of_ray);
	while (x_fisrt_interce >= 0 && x_fisrt_interce < 2000
		&& y_fisrt_interce >= 0 && y_fisrt_interce < 1000
		&& !check_wall_fram(x_fisrt_interce, y_fisrt_interce, y->map, y))
	{
			y_fisrt_interce += ystep;
			x_fisrt_interce += xstep;
	}
	return (distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce, y_fisrt_interce));
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
		x_fisrt_interce_v = floor(y->plr->x_p / 32) * 32 - 0.01;
		xstep_v *= -1;
		ystep_v *= -1;
	}
	y_fisrt_interce_v = y->plr->y_p + ((x_fisrt_interce_v - y->plr->x_p) * tan(y->angle_of_ray));
	while (x_fisrt_interce_v >= 0 && x_fisrt_interce_v < 2000 && y_fisrt_interce_v >= 0
		&& y_fisrt_interce_v < 1000 && !check_wall_fram(x_fisrt_interce_v, y_fisrt_interce_v, y->map, y))
	{
			y_fisrt_interce_v +=	ystep_v;
			x_fisrt_interce_v +=	xstep_v;
	}
	return (distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce_v, y_fisrt_interce_v));
}
