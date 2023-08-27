/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_mini_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:20:39 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 18:07:32 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_direction(char c)
{
	if (c == 'S' || c == 'E' || c == 'W' || c == 'N')
		return (1);
	return (0);
}

void	draw_pixel(int x, int y, unsigned int color, t_cub *yy)
{
	int	i;
	int	j;

	i = 0;
	if (x < 0 || y < 0)
		exit(1);
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			mlx_put_pixel(yy->image, (y * 32) + i, (x * 32) + j, color);
			j++;
		}
		i++;
	}
}

void	draw_cadre(t_cub *y, unsigned int color)
{
	int	i;

	i = 0;
	while (i < 280)
	{
		mlx_put_pixel(y->image, i, 0, color);
		mlx_put_pixel(y->image, 0, i, color);
		mlx_put_pixel(y->image, i, 280, color);
		mlx_put_pixel(y->image, 280, i, color);
		mlx_put_pixel(y->image, i + 1, 1, color);
		mlx_put_pixel(y->image, 1, i + 1, color);
		mlx_put_pixel(y->image, i + 1, 281, color);
		mlx_put_pixel(y->image, 281, i +1, color);
		i++;
	}
}

void	draw_palyer_loop(t_cub *y, t_draw d)
{
	while (d.i < d.size)
	{
		d.j = d.mm;
		while (d.j < d.size)
		{
			mlx_put_pixel(y->image, 140 + d.i, 140 + d.j, d.color);
			mlx_put_pixel(y->image,
				(15 + d.i) * cos(y->plr->derction) + 140,
				(15 + d.j) * sin(y->plr->derction) + 140, 0xffe512);
			d.j++;
		}
		d.i++;
	}
}

void	draw_player(t_cub *y)
{
	t_draw		d;
	static int	effect;

	d.mm = 0;
	d.i = 0; 
	d.size = 0;
	if (effect < 20)
	{
		d.size = 4;
		d.color = 0xFFFFF;
	}
	else if (effect < 40)
	{
		d.i = -4;
		d.mm = -4;
		d.size = 8;
		d.color = 0x66cdaa;
	}
	else if (effect > 40)
		effect = 0;
	draw_palyer_loop(y, d);
	draw_cadre(y, d.color);
	effect++;
}
