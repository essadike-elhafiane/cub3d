/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:31:09 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/28 16:48:35 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

unsigned int	ft_pixel(unsigned int r, unsigned int g,
							unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

mlx_image_t	*get_img_of_view(t_cub *y)
{
	if (y->h && (y->angle_of_ray > M_PI && y->angle_of_ray < 2 * M_PI))
	{
		y->data_pixel = y->img_n->pixels;
		return (y->img_n);
	}
	else if (y->h)
	{
		y->data_pixel = y->img_s->pixels;
		return (y->img_s);
	}
	if (!y->h && y->angle_of_ray < 3 * M_PI / 2 && y->angle_of_ray > M_PI / 2)
	{
		y->data_pixel = y->img_w->pixels;
		return (y->img_w);
	}
	else
	{
		y->data_pixel = y->img_e->pixels;
		return (y->img_e);
	}
}

void	rander_wall_help(t_wall *w, t_cub *y, int m)
{
	if (w->i < w->top)
		mlx_put_pixel(y->image, m, w->i,
			ft_pixel(y->path->c[0], y->path->c[1], y->path->c[2], 255));
	else if (w->i < w->down)
	{
		w->mm = w->i + (w->height_of_wall / 2) - (1000 / 2);
		w->y_texture = w->mm * ((double)y->imgg->height / w->height_of_wall);
		if ((w->y_texture * y->imgg->width + w->x_texture) * 4 + 3
			< y->imgg->height * y->imgg->width * 4)
			w->color = ft_pixel(y->data_pixel[(w->y_texture
						* y->imgg->width + w->x_texture) * 4],
					y->data_pixel[(w->y_texture
						* y->imgg->width + w->x_texture) * 4 + 1],
					y->data_pixel[(w->y_texture
						* y->imgg->width + w->x_texture) * 4 + 2],
					y->data_pixel[(w->y_texture
						* y->imgg->width + w->x_texture) * 4 + 3]);
		else
			w->color = 0;
		mlx_put_pixel(y->image, m, w->i, w->color);
	}
	else
		mlx_put_pixel(y->image, m,
			w->i, ft_pixel(y->path->f[0], y->path->f[1], y->path->f[2], 255));
	w->i++;
}

void	randerwall(t_cub *y, int m)
{
	t_wall	w;

	w.i = 0;
	y->distancee = y->distancee * cos(y->angle_of_ray - y->plr->derction);
	w.height_of_wall = 60000 / y->distancee;
	w.top = (1000 / 2) - (w.height_of_wall / 2);
	w.down = (1000 / 2) + (w.height_of_wall / 2);
	if (w.top < 0)
		w.top = 0;
	if (w.down > 1000)
		w.down = 1000;
	y->imgg = get_img_of_view(y);
	if (!y->h)
		w.x_texture = (int)((y->hitwall_y_v / 32)
				* y->imgg->width) % y->imgg->width;
	else 
		w.x_texture = (int)((y->hitwall_x * y->imgg->width) / 32)
			% y->imgg->width;
	while (w.i < 1000)
	{
		rander_wall_help(&w, y, m);
	}
}
