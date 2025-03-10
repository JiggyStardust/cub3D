/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:44:46 by sniemela          #+#    #+#             */
/*   Updated: 2025/03/07 13:44:47 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		get_index_of_rov_and_col(t_data *data, int x, int y, enum dir_type gear)
{
	float	i;

	// printf("player angle: %f\n", data->player.angle);
	if (gear == FORWARD)
	{
		if (data->player.angle > PI / 2 && data->player.angle < 3 * PI / 2)
			x++;
		if (data->player.angle > PI && data->player.angle < 2 * PI)
			y++;
	}
	else if (gear == REVERSE)
	{
		if (data->player.angle > 3 * PI / 2 || data->player.angle < PI / 2)
			x++;
		if (data->player.angle < PI && data->player.angle > 0)
			y++;
	}
	else if (gear == LEFT)
	{
		if (data->player.angle < 2 * PI && data->player.angle > PI)
			x++;
		if (data->player.angle < PI / 2 || data->player.angle > 3 * PI / 2)
			y++;
	}
	else if (gear == RIGHT)
	{
		if (data->player.angle > 0 && data->player.angle < PI)
			x++;
		if (data->player.angle > PI / 2 && data->player.angle < 3 * PI / 2)
			y++;
	}
	i = y * data->map_info.width + x;
	return (i);
}

void	move_up_down(t_data *data)
{
	float	x;
	float	y;
	int		i;

	// printf("p_y: %f, p_x: %f, p_a: %f\n", data->player.y, data->player.x, data->player.angle);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		x = data->player.x - data->player.d_x;
		y = data->player.y - data->player.d_y;
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 0);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 0);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		x = data->player.x + data->player.d_x;
		y = data->player.y + data->player.d_y;
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 1);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 1);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
//	i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(data->player.y), 0); // for message printing.
}

void	move_left_right(t_data *data)
{
	float	x;
	float	y;
	int		i;

	// printf("p_y: %f, p_x: %f, p_a: %f\n", data->player.y, data->player.x, data->player.angle);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		x = data->player.x + cos(data->player.angle + PI / 2) * MOVE_SPEED; // make own variable to player.d_x for moving right and left
		y = data->player.y + sin(data->player.angle + PI / 2) * MOVE_SPEED; // make own variable to player.d_y for moving right and left
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 2);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 2);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		x = data->player.x - cos(data->player.angle + PI / 2) * MOVE_SPEED;
		y = data->player.y - sin(data->player.angle + PI / 2) * MOVE_SPEED;
		i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(y), 3);
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = get_index_of_rov_and_col(data, (int)(x), (int)(data->player.y), 3);
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
	// i = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(data->player.y), 0); // for message_printing.
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
	data->mini_p_img->instances[0].x = data->player.x * TILE_MINI;
	data->mini_p_img->instances[0].y = data->player.y * TILE_MINI;
}

// void draw_player(t_data *data) // Using mlx_put_pixel and mlx_image_to_window
// {
// 	int center_x = TILE_MINI / 2;
// 	int center_y = TILE_MINI / 2;
// 	int	y;
// 	int	x;

// 	mlx_delete_image(data->mlx, data->p_img);
// 	data->p_img = mlx_new_image(data->mlx, TILE_MINI, TILE_MINI);
// 	y = -6;
// 	while (y <= 6)
// 	{
// 		x = -6;
// 		while (x <= 6)
// 		{
// 			mlx_put_pixel(data->p_img, center_x + x, center_y + y, 0xFF0000FF);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_image_to_window(data->mlx, data->p_img, data->player.x * TILE_MINI, data->player.y * TILE_MINI);
// }

void	movement(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	move_up_down(data);
	move_left_right(data);
	turn_player(data);
	move_player_image(data); // moving player pixture using instances
	//draw_player(data); // using mlx_put_pixel
}
