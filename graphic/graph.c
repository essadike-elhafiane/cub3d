/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:33:28 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/22 22:26:08 by eelhafia         ###   ########.fr       */
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
			// mlx_put_pixel(image, (y * 32) , (x * 32), 0x0FFFFF);

			j++;
		}
		// mlx_put_pixel(image, (y * 32) + i , (x * 32), 0x0FFFFF);
		i++;
	}
}

void draw_line(t_cub *data, double dis, double rotation)
{
	double end_x = data->plr->x_p + dis * cos(rotation);
	double end_y = data->plr->y_p + dis * sin(rotation);

	int x0 = data->plr->x_p;
	int y0 = data->plr->y_p;
	int x1 = (int)end_x;
	int y1 = (int)end_y;
	
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	
	while (1) {
	    mlx_put_pixel(image, x0, y0, 0x000000FF);
		if ((x0 == x1) && (y0 == y1))
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) 
		{
			err += dx;
			y0 += sy;
		}
	}	
}

int check_is_wall(double y, double x, t_cub *data)
{
	// if (y >= 100 || x >= 100)
	// 	return 1;
	int idy  = y / 32;
	int idx = x / 32;
	int idy1  = (y + 1) / 32;
	int idy_1  = (y - 1) / 32;
	int idx1 = (x + 1) / 32;
	if (y < 0)
		return (1);
	if (x < 0)
		return (1);
	// printf("x == %d | y == %d | c == %c \n", idx, idy, data->map[idy + 9][idx + 1]);
	if (data->map[idy][idx] && (data->map[idy][idx] == '1' || data->map[idy][idx1] == '1' \
	|| data->map[idy1][idx] == '1' || data->map[idy_1][idx] == '1'))
		return 1;
	// if (!map[idy + 9][idx + 1] || map[idy + 9][idx + 1] == '1')
	// 	return (1);
	return (0);
}

double distance_p(double x, double y, double x1, double y1)
{
	return(sqrt(((x1-x) * (x1-x)) + ((y1-y) * (y1 - y))));
}
int angle = 60;

int check_wall_fram(double x, double y, char **map, t_cub *data)
{
	int xx = (int)floor(x / 32);
	// int xx1 = (int)floor((x + 1) / 32);
	// int xx_1 = (int)floor((x - 1) / 32);
	int yy = (int)floor(y / 32);
	// int yy_1 = (int)floor((y - 1 )/ 32);
	// int yy1 = (int)floor((y + 1) / 32);
	// int yy = (int)floor(y / 32);
	if (yy < 0 || yy >= data->hight_map)
		return (1);
	if (xx < 0 || xx >= ft_strlen(map[yy]))
		return (1);
	if (map[yy][xx] == '1' || map[yy][xx] == '1' || map[yy][xx] == '1' || map[yy][xx] == '1' || map[yy][xx] == '1')
		return (1);
	return (0);
}

void frame_playr(void *f)
{
	t_cub *y = f;
	int j = 0;
	int i = 0;
	while (i < 1)
	{
		j = 0;
		while (j < 1)
		{
			mlx_put_pixel(image, y->plr->x_p + i , j + y->plr->y_p , 0xFFFF00);
			j++;
		}
		i++;
	}

	int m = 0;
	double dictence_h = 0;
	double dictence_v = 0;

	y->angle_of_ray = y->plr->derction - (deg2rad(30));
	while (m < 2000)
	{
		if(y->angle_of_ray < 0){
			y->angle_of_ray += 2*M_PI;
		}
		else if(y->angle_of_ray >=2 * M_PI)
		{
			y->angle_of_ray -= 2 * M_PI;
		}
		dictence_h = dictance_horizontal(y);
		dictence_v = dictance_virtical(y);
		y->h = 0;
		if (dictence_h < dictence_v)
			{
				// draw_line(y, dictence_h, y->angle_of_ray);
				y->distancee = dictence_h;
				y->h = 1;
			}
		else
			{
				// draw_line(y, dictence_v, y->angle_of_ray);
				y->distancee = dictence_v;
			}
		randerwall(y, m);
		y->angle_of_ray += deg2rad(60) / 2000;
		m++;
	}
}


mlx_image_t *get_img_of_view(t_cub *y)
{
	// up right
	if (y->angle_of_ray >= 3 * M_PI / 2 && y->angle_of_ray <= 2 * M_PI)
		return (y->img_e);
	if (y->angle_of_ray < 3 * M_PI / 2 && y->angle_of_ray >= M_PI)
		return (y->img_n);
	if (y->angle_of_ray <=  M_PI / 2 && y->angle_of_ray > 0)
		return (y->img_s);
	if (y->angle_of_ray >  M_PI / 2 && y->angle_of_ray < M_PI)
		return (y->img_w);
	return (NULL);
}

void	randerwall(t_cub *y, int m)
{
	int i;

	i = 0;
	int height_of_wall = 20000 / y->distancee;
	int top = (1000 / 2) - (height_of_wall / 2);
	int down = (1000 / 2) + (height_of_wall / 2);
	top = top < 0 ? 0 : top;
	down = down > 1000 ? 1000 : down;
	int x_texture;
	y->imgg = get_img_of_view(y);
	if (!y->h)
		x_texture = (int )y->hitwall_y_v % y->imgg->width;
	else
		x_texture = (int )y->hitwall_x % y->imgg->width;

	int y_texture;
		
	while (i < 1000)
	{
		if (i < top)
			mlx_put_pixel(image, m, i, 0xF0FFF0FF);
		else if (i < down)
		{
				int mm = i +( height_of_wall / 2) - (1000 / 2);
				y_texture = mm * ((float)y->imgg->width / height_of_wall);
				// y_texture = i;
			 	mlx_put_pixel(image, m ,  i, y->data_pixel[y_texture * y->imgg->width + x_texture]);
		}
		else
			// while(i < i + 4 && i < 1000)
			mlx_put_pixel(image, m, i, 0xc3f5c3FF);
		i++;
	}
}

void ft_hook1(void* param)
{
	t_cub* y = param;

	if (mlx_is_key_down(y->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(y->mlx);
	if (mlx_is_key_down(y->mlx, MLX_KEY_UP))
	{
		if (!check_is_wall(y->plr->y_p + 2 * sin(y->plr->derction), y->plr->x_p + 2 * cos(y->plr->derction), y))
		{
			y->plr->y_p += 2 *sin(y->plr->derction);
			y->plr->x_p += 2 *cos(y->plr->derction);
		}
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_DOWN))
	{
		if (!check_is_wall(y->plr->y_p - 2 * sin(y->plr->derction), y->plr->x_p - 2 * cos(y->plr->derction), y))
		{
			y->plr->y_p -= 2 *sin(y->plr->derction);
			y->plr->x_p -= 2 *cos(y->plr->derction);
		}
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_LEFT))
	{
		y->plr->derction -= 2 * M_PI / 180;
		if (y->plr->derction < 0)
				y->plr->derction = (2 * M_PI) + y->plr->derction;
		
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_RIGHT))
	{
		y->plr->derction += 2 * M_PI / 180;
		if (y->plr->derction  >= 2 * M_PI)
				y->plr->derction  = 0;
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
	while (y->map[i])
	{
		int j = 0;
		while (y->map[i][j])
		{
			if (y->map[i][j] == '0' || check_direction(y->map[i][j]))
				draw_pixel(i, j, 0xFFFFFF0);
			if (y->map[i][j] == '1')
				draw_pixel(i, j, 0xE23535FF);
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

void    graphic(char **map, char **map_only)
{
    t_cub y;
    y.map = map_only;

	y.plr = malloc(sizeof(t_player));
	y.with_map = ft_strlen(map[9]);
	y.hight_map = ft_strlen_pnt(map_only);
    y.mlx = mlx_init(2000, 1000, "cube3D", false);
   	image = mlx_new_image(y.mlx, 2000, 1000);
	y.img_data_n = mlx_load_png("./i32.png");
	y.img_data_e = mlx_load_png("./i32.png");
	y.img_data_s = mlx_load_png("./i32.png");
	y.img_data_w = mlx_load_png("./i32.png");
	// y.img_data->texture.pixels
	if (!y.img_data_n || !y.img_data_e || !y.img_data_s || !y.img_data_w)
		exit(1);
	y.img_n = mlx_texture_to_image(y.mlx, y.img_data_n);
	y.img_e = mlx_texture_to_image(y.mlx, y.img_data_e);
	y.img_w = mlx_texture_to_image(y.mlx, y.img_data_w);
	y.img_s = mlx_texture_to_image(y.mlx, y.img_data_s);
	
	y.data_pixel = (uint32_t*)y.imgg->pixels;
	int i = 0;
	while (y.map[i])
	{
		int j = 0;
		while (y.map[i][j])
		{
			if (y.map[i][j] == '1')
				draw_pixel(i, j, 0xFFFFFFF);
			if (check_direction(y.map[i][j]))
			{
				y.plr->x_p = j * 32;
				y.plr->y_p = i * 32;
				y.plr->derction = init_direction(y.map[i][j]);
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