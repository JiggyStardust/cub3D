/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/07 10:35:47 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_data(t_data *data)
{
	data->map_info.height = 0;
	data->map_info.width = 0;
	data->map_info.NO = NULL;
	data->map_info.SO = NULL;
	data->map_info.WE = NULL;
	data->map_info.EA = NULL;
	data->map_info.floor_color.found = 0;
	data->map_info.ceiling_color.found = 0;
	data->map = NULL;
	data->player.found = 0;
	data->view = NULL;
}

void	cleanup(t_data *data)
{
	//if (data->file)
		//free(data->file);
	if (data->map)
		free(data->map);
	if (data->map_info.NO)
		free(data->map_info.NO);
	if (data->map_info.SO)
		free(data->map_info.SO);
	if (data->map_info.WE)
		free(data->map_info.WE);
	if (data->map_info.EA)
		free(data->map_info.EA);
}

// float	get_ray_length(t_ray *ray, float map_x, float map_y, int i, t_data *data)
// {
// 	float	hypotenuse;
// 	int		x;
// 	int		y;

// 	x = (int)map_x;
// 	y = (int)map_y;
// 	(void)i;
// 	// if ((float)map_x < ray->x && fmodf((float)map_x, (int)map_x) != 0)
// 	// 	map_x++;
// 	// if ((float)map_y < ray->y && fmodf((float)map_y, (int)map_y) != 0)
// 	// 	map_y++;
// 	ray->dx = fabsf(map_x - ray->x);
// 	printf("i: %d\ndx: %f\n", i, ray->dx);
// 	ray->dy = fabsf(map_y - ray->y);
// 	printf("dy: %f\n", ray->dy);
// 	hypotenuse = sqrt(pow(ray->dx, 2) + pow(ray->dy, 2)); // * cos(PI / 2 - ray.angle); it wasn't supposed to be rayangle, i feel silly
// 	// printf("\n\nhyp1: %f\n", hypotenuse);
// 	hypotenuse = hypotenuse * cos(data->player.angle - ray->angle);
// 	// printf("hyp2: %f\n", hypotenuse);
// 	// printf("the i: %d, abs division: %f\nthe multiplier: %f\n", i, deg, cos(deg));
// 	return (hypotenuse);
// }

void get_pixel(mlx_texture_t *texture, uint32_t *color, int xy)
{
	t_rgb rgb;
	
	if (xy + 3 >= (texture->width * texture->height))
		return ;
	rgb.r = texture->pixels[xy * 4];
	rgb.g = texture->pixels[xy * 4 + 1];
	rgb.b = texture->pixels[xy * 4 + 2];
	rgb.a = texture->pixels[xy * 4 + 3];
	*color = (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

mlx_image_t *draw_ray(t_data *data, t_ray ray, int x, mlx_image_t *img)
{

	float	center;
	float	wall_height;
	int		wall_top;
	double	t_pos;
	uint32_t	text_x;
	double	step;
	uint32_t	color;

	center = HEIGHT / 2;
	wall_height = HEIGHT / ray.len;
	// printf("raylen = %f\n", ray.len);
	//(twidth * ty + tx) * 4
	wall_top = center - wall_height / 2;
	if (wall_top < 0)
		wall_top = 0;
	//get texture_x based on vertical and horizontal hits (ray.side)
	//text_x = get_x(x, ray, data->texture);
	if (ray.side == VERTICAL)
		ray.end_x = ray.y + ray.len2 * sin(ray.angle);
	else
		ray.end_x = ray.x + ray.len2 * cos(ray.angle);
	ray.end_x -= floor((ray.end_x));
	data->text_x = ray.end_x * (double)data->texture->width;
	if ((ray.side == VERTICAL && cos(ray.angle) > 0) || (ray.side == HORIZONTAL && sin(ray.angle) < 0))
	{
		data->text_x = data->texture->width - data->text_x - 1;
	}
	if (data->text_x < 0)
	{
		data->text_x = 0;
	}
	//printf("texture width: %d\n", data->texture->width);
	//printf("x is: %d\n", x);
	if (data->text_x >= data->texture->width)
		data->text_x = data->texture->width - 1;
	text_x = (uint32_t) data->text_x;
	step = (double) data->texture->height / wall_height;
	t_pos = (wall_top - HEIGHT / 2 + wall_height / 2) * step;
	/*if (ray.side)
		color = RED;
	else
		color = DARK_RED;*/
	while (wall_top <= center + wall_height / 2)
	{
		data->text_y = (uint32_t) t_pos;
		if (data->text_y < 0)
			data->text_y = 0;
		if (data->text_y >= data->texture->height)
			data->text_y = (uint32_t) data->texture->height - 1;
		get_pixel(data->texture, &color, (data->texture->width * data->text_y + text_x));
		mlx_put_pixel(img, x, wall_top, color);
		t_pos += step;
		wall_top++;
		if (wall_top == HEIGHT)
			break ;
	}
	return (img);
}

// float	cast_ray(t_data *data, t_ray *ray)
// {
// 	int		map_x;
// 	int		map_y;
// 	float	delta_x;
// 	float	delta_y;
// 	float	side_dist_x;
// 	float	side_dist_y;
// 	int		step_x;
// 	int		step_y;

// 	map_x = (int)ray->x;
// 	map_y = (int)ray->y;

// 	delta_x = (cos(ray->angle) != 0) ? fabs(1 / cos(ray->angle)) : INFINITY;
// 	delta_y = (sin(ray->angle) != 0) ? fabs(1 / sin(ray->angle)) : INFINITY;

// 	step_x = (cos(ray->angle) > 0) ? 1 : -1;
// 	step_y = (sin(ray->angle) > 0) ? 1 : -1;

// 	side_dist_x = (step_x > 0) ? (map_x + 1.0 - ray->x) * delta_x : (ray->x - map_x) * delta_x;
// 	side_dist_y = (step_y > 0) ? (map_y + 1.0 - ray->y) * delta_y : (ray->y - map_y) * delta_y;

// 	// DDA loop: Step through the grid until we hit a wall
// 	while (data->map[map_y * data->map_info.width + map_x] == FLOOR)
// 	{
// 		if (side_dist_x < side_dist_y)  // Move in X direction
// 		{
// 			map_x += step_x;
// 			side_dist_x += delta_x;
// 		}
// 		else  // Move in Y direction
// 		{
// 			map_y += step_y;
// 			side_dist_y += delta_y;
// 		}
// 	}

// 	// Return the final distance to the wall
// 	return (side_dist_x < side_dist_y) ? side_dist_x : side_dist_y;
// }

float	cast_ray(t_data *data, t_ray *ray)
{
	int		map_x;
	int		map_y;
	float	delta_x;
	float	delta_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	//int		last;

	map_x = (int)ray->x;
	map_y = (int)ray->y;

	if (cos(ray->angle) != 0)
		delta_x = fabs(1 / cos(ray->angle));
	if (sin(ray->angle) != 0)
		delta_y = fabs(1 / sin(ray->angle));
	if (cos(ray->angle) > 0)
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - ray->x) * delta_x;
	}
	else if (cos(ray->angle) < 0)
	{
		step_x = -1;
		side_dist_x = (ray->x - map_x) * delta_x;
	}
	else
	{
		step_x = INFINITY;
		side_dist_x = INFINITY;
		delta_y = INFINITY;
	}
	if (sin(ray->angle) > 0)
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - ray->y) * delta_y;
	}
	else if ((sin(ray->angle) < 0))
	{
		step_y = -1;
		side_dist_y = (ray->y - map_y) * delta_y;
	}
	else
	{
		step_y = INFINITY;
		side_dist_y = INFINITY;
		delta_y = INFINITY;
	}
	
	// DDA loop
	int xy = get_index_of_rov_and_col(data, map_x, map_y, 1);
	while (data->map[xy] == FLOOR)
	{
		if (side_dist_x < side_dist_y)  // Move in X direction
		{
			map_x += step_x;
			side_dist_x += delta_x;
			ray->side = VERTICAL; //vertical
		}
		else  // Move in Y direction
		{
			map_y += step_y;
			side_dist_y += delta_y;
			ray->side = HORIZONTAL; //horizontal
		}
		xy = get_index_of_rov_and_col(data, map_x, map_y, 1);
	}
	// printf("side_dist_x: %f\n", side_dist_x);
	// printf("side_dist_y: %f\n\n", side_dist_y);
	//data->text_x = map_x * (double)data->texture->width;
	//ray->end_x = map_x;
	ray->end_y = map_y;
	if (ray->side == VERTICAL)
	{
		side_dist_x -= delta_x;
		//if (cos(ray->angle) > 0)
			//data->text_x = data->texture->width - data->text_x - 1;
	}
	else if (ray->side == HORIZONTAL)
	{
		side_dist_y -= delta_y;
		//if (sin(ray->angle) < 0)
			//data->text_x = data->texture->width - data->text_x - 1;
	}
	//ray->shade = last;
	if (fabs(side_dist_x) < fabs(side_dist_y))
		return (fabs(side_dist_x));
	else
		return (fabs(side_dist_y));
}


mlx_image_t	*raycaster(t_data *data)
{
	t_ray 		ray;
	int			i;
	//mlx_image_t *img;

	if (data->view != NULL)
		mlx_delete_image(data->mlx, data->view);
	data->view = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ray.x = data->player.x;
	ray.y = data->player.y;
	ray.angle = data->player.angle - (33.0 / 180 * PI);

	// Ensure angle is within 0 to 2*PI range
	if (ray.angle > 2 * PI)
		ray.angle -= 2 * PI;
	else if (ray.angle < 0)
		ray.angle += 2 * PI;

	i = 0;
	while (i < WIDTH)
	{
		// Cast a ray and determine its length
		// printf("i: %d\n", i);
		ray.len = cast_ray(data, &ray);
		ray.len2 = ray.len;
		ray.len *= cos(data->player.angle - ray.angle);
		// printf("ray len: %f\n", ray.len);
		// Draw the wall slice based on ray length
		draw_ray(data, ray, i, data->view);

		// Move to the next ray angle
		ray.angle += ((66.0 / 180 * PI) / WIDTH);
		if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		i++;
	}
	return (data->view);
}


int	main(int argc, char **argv)
{
	t_data	data;

	//check if map is valid and parse
	if (argc != 2)
		return (ft_putstr_fd("Example: ./cub3D file.cub\n", 2), 1);
	init_data(&data);
	if (!parsing(&data, argv))
		return (cleanup(&data), 1);
	data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!data.mlx)
		return (false);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	data.player.angle = get_player_angle(data.player.p_dir);
	data.player.d_x = cos(data.player.angle) * MOVE_SPEED;
	data.player.d_y = sin(data.player.angle) * MOVE_SPEED;
	data.texture = mlx_load_png("./textures/zoo.png");
	if (!setup_images(&data))
		terminate_free(&data, 1, "Error\nProblem with setup_images.\n");
	data.view = raycaster(&data);
	if (!images_to_window(&data))
		terminate_free(&data, 1, "Error\nProblem with opening the window.\n");
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &movement, &data);
	mlx_close_hook(data.mlx, &close_window, &data);
	mlx_loop(data.mlx);
	cleanup(&data);
	terminate_free(&data, 0, NULL);
	return (0);
}
