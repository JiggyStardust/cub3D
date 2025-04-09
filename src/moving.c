/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:44:46 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/09 12:50:53 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	move_up_down(t_data *data)
{
	int		i;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player.new_x = data->player.x + data->player.d_x;
		data->player.new_y = data->player.y + data->player.d_y;
		i = get_index(data, (int)(data->player.x), (int)(data->player.new_y));
		if (data->map[i] == FLOOR)
			data->player.y = data->player.new_y;
		i = get_index(data, (int)(data->player.new_x), (int)(data->player.y));
		if (data->map[i] == FLOOR)
			data->player.x = data->player.new_x;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player.new_x = data->player.x - data->player.d_x;
		data->player.new_y = data->player.y - data->player.d_y;
		i = get_index(data, (int)(data->player.x), (int)(data->player.new_y));
		if (data->map[i] == FLOOR)
			data->player.y = data->player.new_y;
		i = get_index(data, (int)(data->player.new_x), (int)(data->player.y));
		if (data->map[i] == FLOOR)
			data->player.x = data->player.new_x;
	}
}

void	move_left_right(t_data *data)
{
	int		i;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player.new_x = data->player.x - data->player.d_lr_x;
		data->player.new_y = data->player.y - data->player.d_lr_y;
		i = get_index(data, (int)(data->player.x), (int)(data->player.new_y));
		if (data->map[i] == FLOOR)
			data->player.y = data->player.new_y;
		i = get_index(data, (int)(data->player.new_x), (int)(data->player.y));
		if (data->map[i] == FLOOR)
			data->player.x = data->player.new_x;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player.new_x = data->player.x + data->player.d_lr_x;
		data->player.new_y = data->player.y + data->player.d_lr_y;
		i = get_index(data, (int)(data->player.x), (int)(data->player.new_y));
		if (data->map[i] == FLOOR)
			data->player.y = data->player.new_y;
		i = get_index(data, (int)(data->player.new_x), (int)(data->player.y));
		if (data->map[i] == FLOOR)
			data->player.x = data->player.new_x;
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
	data->player.d_lr_x = cos(data->player.angle + PI / 2) * MOVE_SPEED;
	data->player.d_lr_y = sin(data->player.angle + PI / 2) * MOVE_SPEED;
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
	if (data->minimap)
		draw_minimap_rays(data);
	mlx_set_instance_depth(data->view->instances, 3);
	if (data->minimap)
	{
		mlx_set_instance_depth(data->minimap->instances, 4);
		mlx_set_instance_depth(data->ray->instances, 5);
	}
}
