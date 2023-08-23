/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:33:28 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/23 23:04:39 by eelhafia         ###   ########.fr       */
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

unsigned int ft_pixel(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_pixel(int x, int y, unsigned int color)
{
	int i = 0;
	
	if (x < 0 || y < 0)
		exit(1);
	while (i < 32)
	{
		int j = 0;
		while (j < 32)
		{
			mlx_put_pixel(image, (y* 32 ) + i ,( x * 32) + j, color);
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
	int idy  = y / 32;
	int idx = x / 32;
	int idy1  = (y + 1) / 32;
	int idy_1  = (y - 1) / 32;
	int idx1 = (x + 1) / 32;
	if (y < 0)
		return (1);
	if (x < 0)
		return (1);
	if (data->map[idy][idx] && (data->map[idy][idx] == '1' || data->map[idy][idx1] == '1' \
	|| data->map[idy1][idx] == '1' || data->map[idy_1][idx] == '1' ))
		return 1;
	if (data->map[idy][idx] && (data->map[idy][idx] == ' ' || data->map[idy][idx1] == ' ' \
	|| data->map[idy1][idx] == ' ' || data->map[idy_1][idx] == ' ' ))
		return 1;
	if (data->map[(int)(data->plr->y_p / 32)][(int)(x / 32)] == '1' && data->map[idy][(int)(data->plr->x_p / 32)] == '1')
		return (1);
	return (0);
}

double distance_p(double x, double y, double x1, double y1)
{
	return(sqrt(((x1-x) * (x1-x)) + ((y1-y) * (y1 - y))));
}
int angle = 60;

int check_wall_fram(double x, double y, char **map, t_cub *data)
{
	// printf("fddfhd %f | %f\n", x,y);
	// exit(1);
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
	if (map[yy][xx] == '1')
		return (1);
	return (0);
}

void frame_playr(void *f)
{
	t_cub *y = f;
	

	int m = 0;
	double dictence_h = 0;
	double dictence_v = 0;

	y->angle_of_ray = y->plr->derction - (deg2rad(30));
	while (m < 2000)
	{
		if(y->angle_of_ray < 0)
			y->angle_of_ray += 2*M_PI;
		else if(y->angle_of_ray >=2 * M_PI)
			y->angle_of_ray -= 2 * M_PI;
		dictence_h = dictance_horizontal(y);
		dictence_v = dictance_virtical(y);
		y->h = 0;
		if (dictence_h < dictence_v + 1e-8)
			{
				// if (dictence_h > 600)
				// 	dictence_h = 600,00;
				// draw_line(y, dictence_h, y->angle_of_ray);
				y->distancee = dictence_h;
				y->h = 1;
				// printf("%f, %f\n", dictence_h, dictence_v);
			}
		else if (dictence_h >= dictence_v + 1e-8)
			{
				// draw_line(y, dictence_v, y->angle_of_ray);
				// if (dictence_v > 600)
				// 	dictence_v = 600,00;
				y->distancee = dictence_v;
			}
		randerwall(y, m);
		y->angle_of_ray += deg2rad(60) / 2000;
		m++;
	}
	render_next_frame(y);
	draw_player(y);
}


mlx_image_t *get_img_of_view(t_cub *y)
{
	// up right
	if (y->h && (y->angle_of_ray >  M_PI && y->angle_of_ray < 2 * M_PI))
	{
		y->data_pixel = y->img_s->pixels;
		return (y->img_s);
	}
	else if (y->h)
	{
		y->data_pixel = y->img_n->pixels;
		return (y->img_n);
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

void	randerwall(t_cub *y, int m)
{
	int i;
	int x_texture;
	int y_texture;

	i = 0;
	y->distancee = y->distancee * cos(y->angle_of_ray - y->plr->derction);
	int height_of_wall = 60000 / y->distancee;
	int top = (1000 / 2) - (height_of_wall / 2);
	int down = (1000 / 2) + (height_of_wall / 2);
	top = top < 0 ? 0 : top;
	down = down > 1000 ? 1000 : down;
	y->imgg = get_img_of_view(y);
	if (!y->h)
		x_texture = (int )((y->hitwall_y_v / 32) * y->imgg->width) % y->imgg->width;
	else
		x_texture = (int )((y->hitwall_x * y->imgg->width) / 32) % y->imgg->width;
	while (i < 1000)
	{
		if (i < top)
			mlx_put_pixel(image, m, i, ft_pixel(y->path->c[0], y->path->c[1],y->path->c[2], 255));
		else if (i < down)
		{
				int mm = i + ( height_of_wall / 2) - (1000 / 2);
				y_texture = mm * ((double)y->imgg->height / height_of_wall);
				// int m = 0;
				unsigned int color;
				// while (y->data_pixel[m])
				if ((y_texture * y->imgg->width + x_texture) * 4 + 3 < y->imgg->height * y->imgg->width * 4)
				
					color  = ft_pixel(y->data_pixel[(y_texture * y->imgg->width + x_texture) * 4],

					y->data_pixel[(y_texture * y->imgg->width + x_texture) * 4 + 1],

					y->data_pixel[(y_texture * y->imgg->width + x_texture)* 4 + 2],
					
					y->data_pixel[(y_texture * y->imgg->width + x_texture)* 4 + 3]);
					
				else
					color = 0;
				
				// printf("%d\n", y->data_pixel[y_texture * y->imgg->width + x_texture]);
			 	mlx_put_pixel(image, m ,  i, color);
		}
		else
			mlx_put_pixel(image, m, i, ft_pixel(y->path->f[0], y->path->f[1],y->path->f[2], 255));
		i++;
	}
	// free(y->imgg->instances);
	// free(y->imgg->pixels);
	// free(y->imgg);
	// free(y->data_pixel);
}

void render_next_frame1(t_cub *y)
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
				draw_pixel(i, j, 0x000FF);
			j++;
		}
		i++;
	}
}

void ft_hook1(void* param)
{
	t_cub* y = param;

	if (mlx_is_key_down(y->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(y->mlx);
	if (mlx_is_key_down(y->mlx, MLX_KEY_UP) || mlx_is_key_down(y->mlx, MLX_KEY_W))
	{
		if (!check_is_wall(y->plr->y_p + 5 * sin(y->plr->derction), y->plr->x_p + 5 * cos(y->plr->derction), y))
		{
			y->plr->y_p += 5 *sin(y->plr->derction);
			y->plr->x_p += 5 *cos(y->plr->derction);
		}
		y->plr->a_x = y->plr->x_p + 20 * cos(y->plr->derction);
		y->plr->a_y = y->plr->y_p + 20 * sin(y->plr->derction);
	}
	if (mlx_is_key_down(y->mlx, MLX_KEY_DOWN))
	{
		if (!check_is_wall(y->plr->y_p - 5 * sin(y->plr->derction), y->plr->x_p - 5 * cos(y->plr->derction), y))
		{
			y->plr->y_p -= 5 *sin(y->plr->derction);
			y->plr->x_p -= 5 *cos(y->plr->derction);
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
	mlx_delete_image(y->mlx, image);
	image = mlx_new_image(y->mlx, 2000, 1000);
	// render_next_frame1(y);
	frame_playr(y);
	mlx_image_to_window(y->mlx, image, 0, 0);
}

void	draw_player(t_cub *y)
{
	int size;
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
	else if(effect < 40)
	{
		i = -4;
		mm = -4;
		size = 8;
		color = 0x66cdaa;
	}
	else
		effect = 0;
	while (i < size)
	{
		j = mm;
		while (j < size)
		{
			mlx_put_pixel(image, 140 + i , 140 + j , color);
			mlx_put_pixel(image, (15 + i) *  cos(y->plr->derction) + 140,  (15 + j) * sin(y->plr->derction) + 140,  0xFFFFF);
			j++;
		}
		i++;
	}
	
	effect++;
}

void render_next_frame(t_cub *y)
{
	static int effect;
	int i = 0;
	int j;
	unsigned int color;
	
	color = 0x7FEAFF;
	effect = 0;
	
	int tmp = y->plr->x_p;
	int	tmp2 = y->plr->y_p; 
	int x_map;
	tmp -= 140;
	tmp2 -= 140;
	int y_map = tmp2;
	
	int yy;
	int xx;

	yy = 0;
	while(yy < 280)
	{
		xx = 0;
		while(xx < 280)
		{
			// mlx_put_pixel(image, xx  ,yy , 0xFFF);
			xx++;
		}
		yy++;
	}

	
	if(y_map < 0)
		y_map = 0;

	while(y_map < tmp2 + 140 * 2 && y->map[y_map / 32])
	{
		x_map = tmp;
		if (x_map < 0)
			x_map = 0;	
			while((x_map < tmp + 140 * 2) && x_map / 32 < ft_strlen(y->map[y_map / 32]))
			{
					// if(y->map[y_map / 32][x_map / 32] == '0')
					// 	// mlx_put_pixel(image,   ,(x_map  - y->plr->x_p + 140 )  , 0xE23535FF);
					// 	mlx_put_pixel(image, (x_map  - y->plr->x_p + 140 )  , (y_map  - y->plr->y_p + 140) , 0xE23535FF);
					if(y->map[y_map / 32][x_map / 32] == '1')
						// mlx_put_pixel(image, (y_map  - y->plr->y_p + 140)    ,(x_map  - y->plr->x_p + 140 )  ,);
						mlx_put_pixel(image, (x_map  - y->plr->x_p + 140 )  , (y_map  - y->plr->y_p + 140) , 0xE2FFFF);
					// else
					// 	mlx_put_pixel(image, (x_map  - y->plr->x_p + 100 )  , (y_map  - y->plr->y_p + 100) , 0xE23535FF);
				
					x_map++;
			}
		y_map++;
	}
}

int ft_strlen_pnt(char **str)
{
	int i;
	
	i = 0;
	if (!str || !*str)
		return (0);
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

void    graphic(char **map_only, t_path *p)
{
    t_cub y;
    y.map = map_only;
	y.path = p;
	y.plr = malloc(sizeof(t_player));
	if (!y.plr)
		exit(0);
	// y.with_map = ft_strlen(map_only[0]);
	// if (y.with_map == 0)
		// exit(0);
	y.hight_map = ft_strlen_pnt(map_only);
    y.mlx = mlx_init(2000, 1000, "cube3D", false);
   	image = mlx_new_image(y.mlx, 2000, 1000);
	
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
	int i = 0;
	while (y.map[i])
	{
		int j = 0;
		while (y.map[i][j])
		{
			// if (y.map[i][j] == '1')
			// 	draw_pixel(i, j, 0xFFFFFFF);
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
	// exit(1);
	// render_next_frame(&y);
	// mlx_loop_hook(y.mlx, ft_randomize, &y);aaaa
	mlx_loop_hook(y.mlx, ft_hook1, &y);
	mlx_image_to_window(y.mlx, image, 0, 0);
	mlx_loop(y.mlx);
	mlx_delete_texture(y.img_data_e);
	mlx_delete_texture(y.img_data_n);
	mlx_delete_texture(y.img_data_w);
	mlx_delete_texture(y.img_data_s);
	// mlx_delete_image(y.mlx, y.img_e);
	free(p->ea);
	free(p->we);
	free(p->so);
	free(p->no);
	free(y.plr);
	mlx_close_window(y.mlx);
	mlx_delete_image(y.mlx, image);
}

// when we want to calcul a dictance between a and b just we need to transfer it to trangle Ay - By = ab and Ax - Bx = Ac and we will calclut auther line with tng or sin or cos 