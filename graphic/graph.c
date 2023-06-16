/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:33:28 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/16 19:30:26 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

//for convert a degrees to rad 

double deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

static mlx_image_t* image;

int check_direction(char c)
{
	if (c == 'S' || c == 'E' || c == 'W' || c == 'N')
		return (1);
	return (0);
}


// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_pixel(int x, int y, unsigned int color)
{
	int i = 0;
	
	while (i < 32)
	{
		int j = 0;
		while (j < 32)
		{
			mlx_put_pixel(image, (y * 32) + i , (x * 32) + j, color);
			j++;
		}
		i++;
	}
}

void frame_playr(void *f)
{
	t_cub *y = f;
	int j = 0;
	int i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(image, y->plr->x_p + 32  + i , 32 + j + y->plr->y_p , 0xFFFF00);
			j++;
		}
		i++;
	}

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(image, y->plr->a_x + 32  + i , 32 + j + y->plr->a_y , 0xFF3333);
			j++;
		}
		i++;
	}
}

int check_is_wall(char **map, int y, int x, t_cub *data)
{
	int idy  = y / 32;
	int idx = x / 32;
	int idy1  = (y + 1) / 32;
	int idy_1  = (y - 1) / 32;
	int idx1 = (x + 1) / 32;
	if (idy >= data->hight_map)
		return 1;
	if (y < 0)
		return (1);
	if (x < 0)
		return (1);
	if (data->map[idy + 9][idx + 1] && (data->map[idy + 9][idx + 1] == '1' || data->map[idy + 9][idx1 + 1] == '1' \
	|| data->map[idy1 + 9][idx + 1] == '1' || data->map[idy_1 + 9][idx + 1] == '1'))
		return 1;
	// if (!map[idy + 9][idx + 1] || map[idy + 9][idx + 1] == '1')
	// 	return (1);
	return (0);
}

void ft_hook1(void* param)
{
	t_cub* y = param;

	if (mlx_is_key_down(y->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(y->mlx);
	if (mlx_is_key_down(y->mlx, MLX_KEY_UP))
	{
		if (!check_is_wall(y->map, y->plr->y_p + 2 * sin(y->plr->derction), y->plr->x_p + 2 * cos(y->plr->derction), y))
		{
			printf("%f\n", y->plr->derction);
			y->plr->y_p += 2 *sin(y->plr->derction);
			y->plr->x_p += 2 *cos(y->plr->derction);
		}
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_DOWN))
	{
		if (!check_is_wall(y->map, y->plr->y_p - 2 * sin(y->plr->derction), y->plr->x_p - 2 * cos(y->plr->derction), y))
		{
			printf("%f\n", y->plr->derction);
			y->plr->y_p -= 2 *sin(y->plr->derction);
			y->plr->x_p -= 2 *cos(y->plr->derction);
		}
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_LEFT))
	{
		y->plr->derction -= 2 * M_PI / 180;
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_RIGHT))
	{
		y->plr->derction += 2 * M_PI / 180;
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	mlx_delete_image(y->mlx, image);
	image = mlx_new_image(y->mlx, 2000, 1000);
	render_next_frame(y);
	frame_playr(y);
	mlx_image_to_window(y->mlx, image, 0, 0);
}


void render_next_frame(t_cub *y)
{
	int i = 0;
	while (y->map[i + 8])
	{
		int j = 0;
		while (y->map[i + 8][j])
		{
			if (y->map[i + 8][j] == '0' || check_direction(y->map[i + 8][j]))
				draw_pixel(i, j, 0xFFFFFF0);
			if (y->map[i + 8][j] == '1')
				draw_pixel(i, j, 0x000FF);
			j++;
		}
		i++;
	}
}

int ft_strlen_pnt(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

double init_direction(char c)
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

void    graphic(char **map)
{
    t_cub y;
    y.map = map;
	
	y.plr = malloc(sizeof(t_player));
	y.with_map = ft_strlen(map[8]);
	y.hight_map = ft_strlen_pnt(map);
	y.hight_map -= 8;
	printf("%d is with || %d is height\n", y.with_map, y.hight_map);
    y.mlx = mlx_init(2000, 1000, "cube3D", false);

   	image = mlx_new_image(y.mlx, 2000, 1000);
	int i = 0;
	while (y.map[i + 8])
	{
		int j = 0;
		while (y.map[i + 8][j])
		{
			if (y.map[i + 8][j] == '1')
				draw_pixel(i, j, 0xFFFFFFF);
			if (check_direction(y.map[i + 8][j]))
			{
				y.plr->x_p = j * 32;
				y.plr->y_p = i * 32;
				y.plr->derction = init_direction(y.map[i + 8][j]);
				y.plr->a_x = y.plr->x_p + 20 * cos(y.plr->derction);
				y.plr->a_y = y.plr->y_p + 20 * sin(y.plr->derction);
			}
			j++;
		}
		i++;
	}
	// render_next_frame(&y);
	// mlx_loop_hook(y.mlx, ft_randomize, &y);
	mlx_loop_hook(y.mlx, ft_hook1, &y);
	mlx_image_to_window(y.mlx, image, 0, 0);
	mlx_loop(y.mlx);
}

// when we want to calcul a dictance between a and b just we need to transfer it to trangle Ay - By = ab and Ax - Bx = Ac and we will calclut auther line with tng or sin or cos 