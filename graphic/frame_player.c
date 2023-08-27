/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:01:34 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 17:09:16 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	init_frame(t_mini_map *m, t_cub *y)
{
	m->tmp = y->plr->x_p;
	m->tmp2 = y->plr->y_p; 
	m->tmp -= 140;
	m->tmp2 -= 140;
	m->y_map = m->tmp2;
	m->yy = 0;
	while (m->yy < 280)
	{
		m->xx = 0;
		while (m->xx < 280)
			m->xx++;
		m->yy++;
	}
}

void	render_next_frame(t_cub *y)
{
	t_mini_map	m;

	init_frame(&m, y);
	if (m.y_map < 0)
		m.y_map = 0;
	while (m.y_map < m.tmp2 + 140 * 2 && y->map[m.y_map / 32])
	{
		m.x_map = m.tmp;
		if (m.x_map < 0)
			m.x_map = 0;
		while ((m.x_map < m.tmp + 140 * 2)
			&& (size_t)(m.x_map / 32) < ft_strlen(y->map[m.y_map / 32]))
		{
			if (y->map[m.y_map / 32][m.x_map / 32] == '1')
				mlx_put_pixel(y->image, (m.x_map - y->plr->x_p + 140),
					(m.y_map - y->plr->y_p + 140), 0xFFF);
			m.x_map++;
		}
		m.y_map++;
	}
}

void	frame_playr_loop(int m, double distence_v, double distence_h, t_cub *y)
{
	while (m < 2000)
	{
		if (y->angle_of_ray < 0)
			y->angle_of_ray += 2 * M_PI;
		else if (y->angle_of_ray >= 2 * M_PI)
			y->angle_of_ray -= 2 * M_PI;
		distence_h = dictance_horizontal(y);
		distence_v = dictance_virtical(y);
		y->h = 0;
		if (distence_h < distence_v + 0.00000001)
		{
			y->distancee = distence_h;
			y->h = 1;
		}
		else if (distence_h >= distence_v + 0.00000001)
			y->distancee = distence_v;
		randerwall(y, m);
		y->angle_of_ray += deg2rad(60) / 2000;
		m++;
	}
}

void	frame_playr(t_cub *y)
{
	int		m;
	double	distence_v;
	double	distence_h;

	m = 0;
	distence_h = 0;
	distence_v = 0;
	y->angle_of_ray = y->plr->derction - (deg2rad(30));
	frame_playr_loop(m, distence_v, distence_h, y);
	render_next_frame(y);
	draw_player(y);
}
