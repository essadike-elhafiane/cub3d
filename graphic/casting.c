/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:03:08 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 16:43:14 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_wall_fram(double x, double y, char **map, t_cub *data)
{
	int	xx;
	int	yy;

	xx = (int)floor(x / 32);
	yy = (int)floor(y / 32);
	if (yy < 0 || yy >= data->hight_map)
		return (1);
	if (xx < 0 || (size_t)xx >= ft_strlen(map[yy]))
		return (1);
	if (map[yy][xx] == '1')
		return (1);
	return (0);
}

double	distance_p(double x, double y, double x1, double y1)
{
	return (sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y))));
}

double	dictance_horizontal(t_cub *y)
{
	double	ystep;
	double	y_f_h;
	double	x_f_h;
	double	xstep;

	ystep = 32;
	xstep = ystep / tan(y->angle_of_ray);
	if (y->angle_of_ray > 0 && y->angle_of_ray < M_PI)
		y_f_h = floor(y->plr->y_p / 32) * 32 + 32;
	else 
	{
		y_f_h = floor(y->plr->y_p / 32) * 32 - 0.00000001;
		ystep *= -1;
		xstep *= -1;
	}
	x_f_h = y->plr->x_p + (y_f_h - y->plr->y_p) / tan(y->angle_of_ray);
	while (x_f_h >= 0 && y_f_h >= 0 
		&& !check_wall_fram(x_f_h, y_f_h, y->map, y))
	{
		y_f_h += ystep;
		x_f_h += xstep;
	}
	return (y->hitwall_x = x_f_h, y->hitwall_y = y_f_h,
		distance_p(y->plr->x_p, y->plr->y_p, x_f_h, y_f_h));
}

double	dictance_virtical(t_cub *y)
{
	double	x_f_v;
	double	y_f_v;
	double	xstep_v;
	double	ystep_v;

	xstep_v = 32;
	ystep_v = 32 * tan(y->angle_of_ray);
	if (y->angle_of_ray > 3 * M_PI / 2 || y->angle_of_ray < M_PI / 2)
		x_f_v = floor(y->plr->x_p / 32) * 32 + 32;
	else
	{
		x_f_v = floor(y->plr->x_p / 32) * 32 - 0.00000001;
		xstep_v *= -1;
		ystep_v *= -1;
	}
	y_f_v = y->plr->y_p + ((x_f_v - y->plr->x_p) * tan(y->angle_of_ray));
	while (x_f_v >= 0 && y_f_v >= 0
		&& !check_wall_fram(x_f_v, y_f_v, y->map, y))
	{
		y_f_v += ystep_v;
		x_f_v += xstep_v;
	}
	return (y->hitwall_x_v = x_f_v, y->hitwall_y_v = y_f_v,
		distance_p(y->plr->x_p, y->plr->y_p, x_f_v, y_f_v));
}
