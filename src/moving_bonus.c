/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:44:46 by sniemela          #+#    #+#             */
/*   Updated: 2025/03/05 14:43:59 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	move_player(t_data *data)
{
	float	move_speed = 0.1;
	float	turn_speed = 0.1;
	float	x;
	float	y;
	int	i;
	//printf("p_y: %f, p_x: %f, p_a: %f\n", data->player.y, data->player.x, data->player.angle);

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		x = data->player.x - data->player.d_x * move_speed;
		y = data->player.y - data->player.d_y * move_speed;

		/*// if (data->map[(int)y][(int)data->player.x] != '1') How to do this check smoothly with current map?
			data->player.y = y;
		// if (data->map[(int)data->player.y][(int)x] != '1') How to do this check smoothly with current map?
			data->player.x = x;*/
		i = y * data->map_info.width + data->player.x + 1;
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = data->player.y * data->map_info.width + x + 1;
		if (data->map[i] == FLOOR)
			data->player.x = x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		x = data->player.x + data->player.d_x * move_speed;
		y = data->player.y + data->player.d_y * move_speed;

	/*//	if (data->map[(int)y][(int)data->player.x] != '1') How to do this check smoothly with current map?
			data->player.y = y;
	//	if (data->map[(int)data->player.y][(int)x] != '1') How to do this check smoothly with current map?
			data->player.x = x;*/
		i = y * data->map_info.width + data->player.x + 1;
		if (data->map[i] == FLOOR)
			data->player.y = y;
		i = data->player.y * data->map_info.width + x + 1;
		if (data->map[i] == FLOOR)
			data->player.x = x;
		
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle -= turn_speed;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle += turn_speed;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}
	data->player.d_x = cos(data->player.angle) * move_speed;
	data->player.d_y = sin(data->player.angle) * move_speed;
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
	move_player(data);
	move_player_image(data); // moving player pixture using instances
	//draw_player(data); // using mlx_put_pixel
}
