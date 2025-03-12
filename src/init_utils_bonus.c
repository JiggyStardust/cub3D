/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:02:38 by sniemela          #+#    #+#             */
/*   Updated: 2025/03/12 13:19:01 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// int	get_width(char **map)
// {
// 	int	width;
// 	int	i;

// 	i = 0;
// 	width = (int)ft_strlen(map[i]);
// 	while (map[i])
// 	{
// 		if ((int)ft_strlen(map[i]) > width)
// 			width = ft_strlen(map[i]);
// 		i++;
// 	}
// 	width *= TILE_MINI;
// 	return (width);
// }

// int	get_height(char **map)
// {
// 	int	i;
// 	int	height;

// 	i = 0;
// 	while (map[i] != NULL)
// 		i++;
// 	height = i * TILE_MINI;
// 	return (height);
// }

void	get_player_x_y(enum e_type *map, t_data *data)
{
	int	i;
	int	size;
	t_position pos;

	i = 0;
	size = data->map_info.height * data->map_info.width;
	while (i < size)
	{
		if (map[i] == S || map[i] == W || map[i] == N || map[i] == E)
			break ;
		i++;
	}
	pos = get_pos(data, i);
	data->player.x = (float)pos.col;
	data->player.y = (float)pos.row;
}

float	get_player_angle(char dir)
{
	if (dir == 'N')
		return ((PI) / 2);
	else if (dir == 'W')
		return (0.0);
	else if (dir == 'S')
		return ((3 * PI) / 2);
	else
		return (PI);
}
