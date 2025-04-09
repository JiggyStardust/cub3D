/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:44:46 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/09 17:23:53 by sniemela         ###   ########.fr       */
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

void	turn_player(t_data *data, int turn)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= TURN_SPEED;
	else if (turn == 1)
		data->player.angle -= TURN_SPEED * 0.5;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += TURN_SPEED;
	else if (turn == 2)
		data->player.angle += TURN_SPEED * 0.5;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	else if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	data->player.d_x = cos(data->player.angle) * MOVE_SPEED;
	data->player.d_y = sin(data->player.angle) * MOVE_SPEED;
	data->player.d_lr_x = cos(data->player.angle + PI / 2) * MOVE_SPEED;
	data->player.d_lr_y = sin(data->player.angle + PI / 2) * MOVE_SPEED;
}

void	mouse_hook(void *param)
{
	t_data	*data;
	int32_t	x;
	int32_t	y;

	data = (t_data *)param;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
		data->mouse_rotate = true;
	}
	else if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		data->mouse_rotate = false ;
	}
	if (!data->mouse_rotate)
		return ;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x < data->mouse_x)
		turn_player(data, 1);
	else if (x > data->mouse_x)
		turn_player(data, 2);
	data->mouse_x = WIDTH / 2;
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

void	movement(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	move_up_down(data);
	move_left_right(data);
	mouse_hook(data);
	turn_player(data, 0);
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
