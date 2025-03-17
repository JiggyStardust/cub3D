/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:27:59 by sniemela          #+#    #+#             */
/*   Updated: 2025/03/12 12:36:33 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static mlx_image_t	*png_to_resized_img(t_data *data, const char *path_text)
{
	mlx_texture_t	*text;
	mlx_image_t		*img;

	text = mlx_load_png(path_text);
	if (!text)
		return (NULL);
	img = mlx_texture_to_image(data->mlx, text);
	if (!img)
	{
		mlx_delete_texture(text);
		return (NULL);
	}
	mlx_delete_texture(text);
	if (img->width != TILE_MINI || img->height != TILE_MINI)
	{
		if (!mlx_resize_image(img, TILE_MINI, TILE_MINI))
		{
			mlx_delete_image(data->mlx, img);
			return (NULL);
		}
	}
	return (img);
}

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

mlx_image_t *draw_player(t_data *data) // Using mlx_put_pixel and mlx_image_to_window
{
	mlx_image_t *img;
	int	y;
	int	x;

	img = mlx_new_image(data->mlx, 13, 13);
	if (!img)
		return (NULL);
	y = 0;
	while (y <= 12)
	{
		x = 0;
		while (x <= 12)
		{
			mlx_put_pixel(img, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
	return (img);
}

bool	setup_images(t_data *data)
{
	data->ceiling_img = draw_background(data, data->map_info.ceiling_color);
	if (!data->ceiling_img)
		return (false);
	data->floor_img = draw_background(data, data->map_info.floor_color);
	if (!data->floor_img)
		return (false);
	data->mini_f_img = png_to_resized_img(data, "./textures/mini_floor.png");
	if (!data->mini_f_img)
		return (false);
	data->mini_w_img = png_to_resized_img(data, "./textures/mini_wall.png");
	if (!data->mini_w_img)
		return (false);
	// data->mini_p_img = png_to_resized_img(data, "./textures/mini_player.png");
	// if (!data->mini_p_img)
	// 	return (false);
	data->mini_p_img = draw_player(data);
	if (!data->mini_p_img)
		return (false);
	return (true);
}