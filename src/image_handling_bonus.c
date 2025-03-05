/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:27:59 by sniemela          #+#    #+#             */
/*   Updated: 2025/03/04 15:40:11 by sniemela         ###   ########.fr       */
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

bool	setup_images(t_data *data)
{
	data->mini_f_img = png_to_resized_img(data, "./textures/mini_floor.png");
	if (!data->mini_f_img)
		return (false);
	data->mini_w_img = png_to_resized_img(data, "./textures/mini_wall.png");
	if (!data->mini_w_img)
		return (false);
	data->mini_p_img = png_to_resized_img(data, "./textures/mini_player.png");
	if (!data->mini_p_img)
		return (false);
	return (true);
}