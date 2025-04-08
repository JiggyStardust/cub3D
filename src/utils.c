/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:46:53 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/10 11:06:07 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	free_2d_array(char **ptr)
{
	int	i;

	i = -1;
	while (ptr && ptr[++i])
		free(ptr[i]);
	free(ptr);
}

int	is_texture_or_color(char *line)
{
	int	j;

	j = 0;
	if (line[j] == 'N' || line[j] == 'W' || line[j] == 'S' || line[j] == 'E'
		|| line[j] == 'F' || line[j] == 'C' || line[j] == '\n')
	{
		free(line);
		return (1);
	}
	return (0);
}

t_position	get_pos(t_data *data, int i)
{
	t_position	pos;
	int			row;
	int			col;

	pos.col = 0;
	pos.row = 0;
	row = 0;
	while (row <= i)
	{
		pos.row++;
		row += data->map_info.width;
	}
	pos.row--;
	col = pos.row * data->map_info.width;
	while (col++ < i)
		pos.col++;
	return (pos);
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
		ft_putstr_fd("Found texture '", 2);
		ft_putstr_fd(src, 2);
		ft_putstr_fd("' multiple times\n", 2);
		return (0);
	}
	*dest = ft_strdup(src);
	if (!*dest)
		return (ft_putstr_fd("Alloctation failed\n", 2), 0);
	return (1);
}

int	set_color(char **rgb, t_rgb *colors)
{
	if (colors->found == 1)
		return (ft_putstr_fd("Color found multiple times\n", 2), 0);
	colors->found = 1;
	colors->r = ft_atoi(rgb[0]);
	colors->g = ft_atoi(rgb[1]);
	colors->b = ft_atoi(rgb[2]);
	if (colors->r > 255 || colors->r < 0 || colors->g > 255 || \
		colors->g < 0 || colors->b > 255 || colors->b < 0)
		return (ft_putstr_fd("Color out of range\n", 2), 0);
	return (1);
}
