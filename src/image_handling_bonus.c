/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:27:59 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/08 13:04:23 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

mlx_image_t	*draw_background(t_data *data, t_rgb rgb)
{
	mlx_image_t *img;
	uint32_t	color;
	int			x;
	int			y;

	y = 0;
	color = (uint32_t)((rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8) | 255);
	img = mlx_new_image(data->mlx, WIDTH, HEIGHT / 2);
	if (!img)
		return (NULL);
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	return (img);
}

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
	while (i < data->tile_mini)
	{
		j = 0;
		while (j < data->tile_mini)
		{
			mlx_put_pixel(data->minimap, x * data->tile_mini + j, y * data->tile_mini + i, color);
			j++;
		}
		i++;
	}
}

int		define_minimap_tile(int map_width, int map_height)
{
	int	tile;

	tile = 29;
	while (map_height * tile < 450)
		tile++;
	while (map_width * tile > WIDTH)
		tile--;
	if (tile < 30)
		tile = 0;
	return (tile);
}

bool	setup_images(t_data *data)
{
	int			i;
	t_position	pos;

	i = 0;
	data->minimap = NULL;
	data->tile_mini = define_minimap_tile(data->map_info.width, data->map_info.height);
	data->ceiling_img = draw_background(data, data->map_info.ceiling_color);
	if (!data->ceiling_img)
		return (false);
	data->floor_img = draw_background(data, data->map_info.floor_color);
	if (!data->floor_img)
		return (false);
	if (data->tile_mini >= 30)
		data->minimap = mlx_new_image(data->mlx, data->map_info.width * data->tile_mini, data->map_info.height * data->tile_mini);
	if (data->tile_mini >= 30 && !data->minimap)
		return (false);
	if (data->minimap)
	{
		while (i < data->map_info.width * data->map_info.height)
		{
			pos = get_pos(data, i);
			draw_minimap(data, data->map[i], pos.col, pos.row);
			i++;
		}
	}
	return (true);
}
