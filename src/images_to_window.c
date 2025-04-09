/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_to_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:22:23 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/09 12:50:39 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

bool	images_to_window(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->ceiling_img, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(data->mlx, data->floor_img, 0, HEIGHT / 2) == -1)
		return (false);
	if (mlx_image_to_window(data->mlx, data->view, 0, 0) == -1)
		return (false);
	if (data->minimap)
	{
		if (mlx_image_to_window(data->mlx, data->minimap, 0, 0) == -1)
			return (false);
	}
	return (true);
}
