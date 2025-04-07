/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:44:46 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/07 14:05:34 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		get_index_of_rov_and_col(t_data *data, int x, int y, enum dir_type gear)
{
	float	i;
	(void)gear;
	i = y * data->map_info.width + x;
	return (i);
}

void	move_up_down(t_data *data)
{
	float	x;
	float	y;
	int		i;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		x = data->player.x + data->player.d_x;
		y = data->player.y + data->player.d_y;
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 0);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 0);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		x = data->player.x - data->player.d_x;
		y = data->player.y - data->player.d_y;
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 1);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 1);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
}

void	draw_minimap_rays(t_data *data)
{
	// float	ray_len;
	int		i;
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	map_x;
	float	map_y;
	int		xy;

	i = 0;
	mlx_delete_image(data->mlx, data->ray);
	data->ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ray_x = data->player.x;
	ray_y = data->player.y;
	ray_angle = data->player.angle - (33.0 / 180 * PI);
	if (ray_angle >= 2 * PI)
		ray_angle -= 2 * PI;
	else if (ray_angle < 0)
		ray_angle += 2 * PI;
	while (i <= 66)
	{
		xy = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(data->player.y), 1);
		map_y = ray_y;
		map_x = ray_x;
		while (data->map[xy] == FLOOR)
		{
			map_x += cos(ray_angle) * 0.01;
			map_y += sin(ray_angle) * 0.01;
			xy = get_index_of_rov_and_col(data, (int)map_x, (int)map_y, 1);
			mlx_put_pixel(data->ray, map_x * data->tile_mini - 5, map_y * data->tile_mini - 5, RED);
		}
		ray_angle += (1.0/180 * PI);
		if (ray_angle >= 2 * PI)
			ray_angle -= 2 * PI;
		i++;
	}
	mlx_image_to_window(data->mlx, data->ray, data->player.x, data->player.y);
}

void	move_left_right(t_data *data)
{
	float	x;
	float	y;
	int		i;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		x = data->player.x - cos(data->player.angle + PI / 2) * MOVE_SPEED;
		y = data->player.y - sin(data->player.angle + PI / 2) * MOVE_SPEED;
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 2);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 2);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		x = data->player.x + cos(data->player.angle + PI / 2) * MOVE_SPEED;
		y = data->player.y + sin(data->player.angle + PI / 2) * MOVE_SPEED;
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 3);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 3);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
}

void	turn_player(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle -= TURN_SPEED;
		if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle += TURN_SPEED;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}
	data->player.d_x = cos(data->player.angle) * MOVE_SPEED;
	data->player.d_y = sin(data->player.angle) * MOVE_SPEED;
}

void	move_player_image(t_data *data)
{
	data->mini_p_img->instances[0].x = data->player.x * data->tile_mini;
	data->mini_p_img->instances[0].y = data->player.y * data->tile_mini;
}

void	movement(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	move_up_down(data);
	move_left_right(data);
	turn_player(data);
	data->view = raycaster(data);
	mlx_image_to_window(data->mlx, data->view, 0, 0);
	move_player_image(data);
	draw_minimap_rays(data);
	mlx_set_instance_depth(data->view->instances, 3);
	mlx_set_instance_depth(data->minimap->instances, 4);
	mlx_set_instance_depth(data->mini_p_img->instances, 5);
	mlx_set_instance_depth(data->ray->instances, 6);
}
