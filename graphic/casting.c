/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:03:08 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/20 19:40:54 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double  dictance_horizontal(t_cub *y)
{
    double ystep = 32;
    double y_fisrt_interce = floor(y->plr->y_p / 32) * 32;
	double xstep = ystep / tan(y->angle_of_ray);
	int flg = 0;
	
	// DOwn
	if (y->angle_of_ray > 0 && y->angle_of_ray  < M_PI)
	{
		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 + 32;
		flg = 1;
	}
	// up
	else 
		y_fisrt_interce = floor(y->plr->y_p / 32) * 32 - 1;
	
	double x_fisrt_interce = y->plr->x_p + ( y_fisrt_interce - y->plr->y_p ) / tan(y->angle_of_ray);
	
	if (!flg)
	{
		ystep *= -1;
		xstep *= -1;
	}
		// left
	while (x_fisrt_interce >= 0 && x_fisrt_interce < 2000
		&& y_fisrt_interce >= 0 && y_fisrt_interce < 1000 && !check_wall_fram(x_fisrt_interce, y_fisrt_interce, y->map, y))
	{
	// right
		y_fisrt_interce += ystep;
		x_fisrt_interce += xstep;
	}
	return (distance_p(y->plr->x_p, y->plr->y_p, x_fisrt_interce, y_fisrt_interce));
}

double  dictance_virtical(t_cub *y)
{
    int c = 0;
	float	a_x = 0;
	float	a_y = 0;

	if (y->angle_of_ray > 3 * M_PI / 2 || y->angle_of_ray < M_PI/2)
	{
		a_x = floor(y->plr->x_p / 32) * 32 + 32;
		c = 1;
	}
	else
		a_x = floor(y->plr->x_p / 32) * 32 - 1;
	// printf("rad : %f  x = %f y = %f\n", y->angle_of_ray, a_x, a_y);
	
	a_y = y->plr->y_p + ((a_x - y->plr->x_p) * tan(y->angle_of_ray))  - 0.01;
	while (a_x >= 0 && a_x < 2000 && a_y >= 0 && a_y < 1000 && !check_wall_fram(a_x, a_y, y->map, y))
	{
		if (c)
		{
			a_y +=	32 * tan(y->angle_of_ray);
			a_x +=	32;
		}
		else
		{
			a_y -=	32 * tan(y->angle_of_ray);
			a_x -=	32; 
		}
	}
	return (distance_p(y->plr->x_p, y->plr->y_p, a_x, a_y));
}
