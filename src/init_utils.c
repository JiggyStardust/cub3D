/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:49:10 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/08 15:52:12 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	get_player_x_y(enum e_type *map, t_data *data)
{
	int			i;
	int			size;
	t_position	pos;

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
		return ((3 * PI) / 2);
	else if (dir == 'W')
		return (0.0);
	else if (dir == 'S')
		return (PI / 2);
	else
		return (PI);
}

t_player	player(char c, int j, t_data *data)
{
	t_player	player;
	t_position	pos;

	if (c == 'N')
		player.p_dir = 'N';
	if (c == 'S')
		player.p_dir = 'S';
	if (c == 'W')
		player.p_dir = 'W';
	if (c == 'E')
		player.p_dir = 'E';
	pos = get_pos(data, j);
	player.x = (float)pos.col;
	player.y = (float)pos.row;
	player.found = 1;
	data->map[j] = FLOOR;
	return (player);
}
