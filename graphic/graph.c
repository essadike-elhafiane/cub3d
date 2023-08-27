/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:33:28 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 17:23:55 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_strlen_pnt(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

double	init_direction(char c)
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

void	init_ang(t_cub *y)
{
	int	i;
	int	j;

	i = 0;
	while (y->map[i])
	{
		j = 0;
		while (y->map[i][j])
		{
			if (check_direction(y->map[i][j]))
			{
				y->plr->x_p = j * 32 + 14;
				y->plr->y_p = i * 32 + 14;
				y->plr->derction = init_direction(y->map[i][j]);
			}
			j++;
		}
		i++;
	}
}

void	houk_and_free(t_cub *y, t_path *p)
{
	mlx_loop_hook(y->mlx, ft_hook1, y);
	mlx_loop(y->mlx);
	mlx_delete_texture(y->img_data_e);
	mlx_delete_texture(y->img_data_n);
	mlx_delete_texture(y->img_data_w);
	mlx_delete_texture(y->img_data_s);
	free(p->ea);
	free(p->we);
	free(p->so);
	free(p->no);
	free(y->plr);
	mlx_delete_image(y->mlx, y->image);
	mlx_close_window(y->mlx);
}

void	graphic(char **map_only, t_path *p)
{
	t_cub	y;

	y.map = map_only;
	y.path = p;
	y.mouse_key_down = 0;
	y.plr = malloc(sizeof(t_player));
	if (!y.plr)
		exit(1);
	y.hight_map = ft_strlen_pnt(map_only);
	y.mlx = mlx_init(2000, 1000, "cub3D", false);
	y.image = mlx_new_image(y.mlx, 2000, 1000);
	y.img_data_n = mlx_load_png(p->no);
	y.img_data_e = mlx_load_png(p->ea);
	y.img_data_s = mlx_load_png(p->so);
	y.img_data_w = mlx_load_png(p->we);
	if (!y.img_data_n || !y.img_data_e || !y.img_data_s || !y.img_data_w)
		exit(1);
	y.img_n = mlx_texture_to_image(y.mlx, y.img_data_n);
	y.img_e = mlx_texture_to_image(y.mlx, y.img_data_e);
	y.img_w = mlx_texture_to_image(y.mlx, y.img_data_w);
	y.img_s = mlx_texture_to_image(y.mlx, y.img_data_s);
	init_ang(&y);
	houk_and_free(&y, p);
}
