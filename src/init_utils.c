/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:49:10 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/09 12:13:52 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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

int	add_texture(char *src, char **dest)
{
	if (*dest)
	{
		ft_putstr_fd("Error\nFound texture '", 2);
		if (src)
			ft_putstr_fd(src, 2);
		else
			ft_putstr_fd(" ", 2);
		ft_putstr_fd("' multiple times\n", 2);
		return (0);
	}
	if (!src)
		return (ft_putstr_fd("Error\nNo texture found\n", 2), 0);
	*dest = ft_strdup(src);
	if (!*dest)
		return (ft_putstr_fd("Error\nAlloctation failed\n", 2), 0);
	return (1);
}
