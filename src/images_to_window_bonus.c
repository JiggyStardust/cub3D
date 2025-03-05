/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_to_window_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:22:23 by sniemela          #+#    #+#             */
/*   Updated: 2025/03/04 16:23:38 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static bool	draw_floor_n_walls(t_data *data, enum e_type c, int x, int y)
{
	mlx_image_t	*image;

	if (c == FLOOR || c == S || c == W || c == E || c == N)
		image = data->mini_f_img;
	else if (c == WALL)
		image = data->mini_w_img;
	else
		return (true);
	if (mlx_image_to_window(data->mlx, image, x * TILE_MINI, y * TILE_MINI) == -1)
		return (false);
	return (true);
}

bool	images_to_window(t_data *data)
{
	int			i;
	t_position	pos;

	i = 0;
	while (i < data->map_info.width * data->map_info.height)
	{
		pos = get_pos(data, i);
		if (!draw_floor_n_walls(data, data->map[i], pos.col, pos.row))
			return (false);
		i++;
	}
	if (mlx_image_to_window(data->mlx, data->mini_p_img, data->player.x \
			* TILE_MINI, data->player.y * TILE_MINI) == -1)
		return (false);
	return (true);
}

/*	MITEN KAYTTAA GET_POS T HELMI
int i;
struct pos;

i = 0;
while (i < width * height)
{
	pos = get_pos(map[i]);
	pos.row = y;
	pos.col = x;
	i++;
}
*/