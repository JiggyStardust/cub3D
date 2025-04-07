/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_to_window_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:22:23 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/07 11:57:36 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// static bool	draw_floor_n_walls(t_data *data, enum e_type c, int x, int y)
// {
// 	mlx_image_t	*image;

// 	if (c == FLOOR)
// 		image = data->mini_f_img;
// 	else if (c == WALL)
// 		image = data->mini_w_img;
// 	else
// 		return (true);
// 	if (mlx_image_to_window(data->mlx, image, x * TILE_MINI, y * TILE_MINI) == -1)
// 		return (false);
// 	return (true);
// }

void	 draw_minimap(t_data *data, enum e_type c, int x, int y)
{
	uint32_t	color;
	int			i;
	int			j;

	if (c == FLOOR)
		color = (uint32_t)((255 << 24) | (255 << 16) | (255 << 8) | 255);
	else if (c == WALL)
		color = (uint32_t)((0 << 24) | (0 << 16) | (0 << 8) | 255);
	else
		return ;
	i = 0;
	printf("x: %d, y: %d\n", x, y);
	while (i < TILE_MINI)
	{
		j = 0;
		while (j < TILE_MINI)
		{
			mlx_put_pixel(data->minimap, x * TILE_MINI + j, y * TILE_MINI + i, color);
			j++;
		}
		i++;
	}
}


bool	images_to_window(t_data *data)
{
	int			i;
	t_position	pos;

	i = 0;
	if (mlx_image_to_window(data->mlx, data->ceiling_img, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(data->mlx, data->floor_img, 0, HEIGHT / 2) == -1)
		return (false);
	// while (i < data->map_info.width * data->map_info.height)
	// {
	// 	pos = get_pos(data, i);
	// 	if (!draw_floor_n_walls(data, data->map[i], pos.col, pos.row))
	// 		return (false);
	// 	i++;
	// }
	while (i < data->map_info.width * data->map_info.height)
	{
		pos = get_pos(data, i);
		draw_minimap(data, data->map[i], pos.col, pos.row);
		i++;
	}
	if	(mlx_image_to_window(data->mlx, data->view, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(data->mlx, data->minimap, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(data->mlx, data->mini_p_img, data->player.x \
			* TILE_MINI, data->player.y * TILE_MINI) == -1)
		return (false);
	return (true);
}
