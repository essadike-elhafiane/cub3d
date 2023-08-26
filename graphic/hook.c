/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:30:41 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/26 23:11:44 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	mouse_event(t_cub *y)
{
	if (mlx_is_mouse_down(y->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& y->mouse_key_down == 0)
	{
		mlx_set_mouse_pos(y->mlx, 1000, 500);
		mlx_set_cursor_mode(y->mlx, MLX_MOUSE_HIDDEN);
		y->mouse_key_down = 1;
	}
	else if (!mlx_is_mouse_down(y->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& y->mouse_key_down == 1)
		y->mouse_key_down = 0;
	mlx_get_mouse_pos(y->mlx, &y->x_mouse, &y->y_mouse);
	if (y->mouse_key_down && y->x_mouse > 1000)
		y->plr->derction += 2 * M_PI / 180;
	else if (y->mouse_key_down && y->x_mouse < 1000)
		y->plr->derction -= 2 * M_PI / 180;
	if (mlx_is_key_down(y->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(y->mlx);
}

void	view_left_right(t_cub *y)
{
	if (mlx_is_key_down(y->mlx, MLX_KEY_LEFT))
	{
		y->plr->derction -= 2 * M_PI / 180;
		if (y->plr->derction < 0)
			y->plr->derction = (2 * M_PI) + y->plr->derction;
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_RIGHT))
	{
		y->plr->derction += 2 * M_PI / 180;
		if (y->plr->derction >= 2 * M_PI)
			y->plr->derction = 0;
	}
	mlx_delete_image(y->mlx, y->image);
	y->image = mlx_new_image(y->mlx, 2000, 1000);
	frame_playr(y);
	mlx_image_to_window(y->mlx, y->image, 0, 0);
}

void	key_d_a(t_cub *y)
{
	if (mlx_is_key_down(y->mlx, MLX_KEY_D) || mlx_is_mouse_down(y->mlx, 2))
	{
		if (!check_is_wall(y->plr->y_p + 2 * cos(y->plr->derction),
				y->plr->x_p - 2 * sin(y->plr->derction), y))
		{
			y->plr->y_p += 2 * cos(y->plr->derction);
			y->plr->x_p -= 2 * sin(y->plr->derction);
		}
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_A))
	{
		if (!check_is_wall(y->plr->y_p - 2 * cos(y->plr->derction),
				y->plr->x_p + 2 * sin(y->plr->derction), y))
		{
			y->plr->y_p -= 2 * cos(y->plr->derction);
			y->plr->x_p += 2 * sin(y->plr->derction);
		}
	}
}

void	ft_hook1(void	*param)
{
	t_cub	*y;

	y = param;
	mouse_event(y);
	if (mlx_is_key_down(y->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(y->mlx, MLX_KEY_W))
	{
		if (!check_is_wall(y->plr->y_p + 5 * sin(y->plr->derction),
				y->plr->x_p + 5 * cos(y->plr->derction), y))
		{
			y->plr->y_p += 5 * sin(y->plr->derction);
			y->plr->x_p += 5 * cos(y->plr->derction);
		}
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(y->mlx, MLX_KEY_S))
	{
		if (!check_is_wall(y->plr->y_p - 5 * sin(y->plr->derction),
				y->plr->x_p - 5 * cos(y->plr->derction), y))
		{
			y->plr->y_p -= 5 * sin(y->plr->derction);
			y->plr->x_p -= 5 * cos(y->plr->derction);
		}
	}
	view_left_right(y);
}
