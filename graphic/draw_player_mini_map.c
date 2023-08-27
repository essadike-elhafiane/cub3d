/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_mini_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:20:39 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 17:23:02 by eelhafia         ###   ########.fr       */
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

void	draw_player(t_cub *y)
{
	int size = 0;
	static int effect;
	unsigned int color;
	int j;
	int i = 0;
	int mm = 0;

	if (effect < 20)
	{
		size = 4;
		color = 0xFFFFF;
	}
	else if (effect < 40)
	{
		i = -4;
		mm = -4;
		size = 8;
		color = 0x66cdaa;
	}
	else if (effect > 40)
		effect = 0;
	while (i < size)
	{
		j = mm;
		while (j < size)
		{
			mlx_put_pixel(y->image, 140 + i, 140 + j, color);
			mlx_put_pixel(y->image,
				(15 + i) * cos(y->plr->derction) + 140,
				(15 + j) * sin(y->plr->derction) + 140, 0xffe512);
			j++;
		}
		i++;
	}
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
	effect++;
}
