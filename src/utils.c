/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:46:53 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/08 15:48:23 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	get_index(t_data *data, int x, int y)
{
	float	i;

	i = y * data->map_info.width + x;
	return (i);
}

int	is_texture_or_color(char *line, int j)
{
	int	i;

	i = 0;
	if (line[i] == 'N' || line[i] == 'W' || line[i] == 'S' || line[i] == 'E'
		|| line[i] == 'F' || line[i] == 'C' || (line[i] == '\n' && j == 0))
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

int	invalid_values(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]) && rgb[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	set_color(char **rgb, t_rgb *colors)
{
	if (colors->found == 1)
		return (ft_putstr_fd("Error\nColor found multiple times\n", 2), 0);
	colors->found = 1;
	if (invalid_values(rgb))
		return (ft_putstr_fd("Error\nError with color values\n", 2), 0);
	colors->r = ft_atoi(rgb[0]);
	if (colors->r == 0 && *rgb[0] != '0')
		return (ft_putstr_fd("Error\nError with color values\n", 2), 0);
	colors->g = ft_atoi(rgb[1]);
	if (colors->g == 0 && *rgb[1] != '0')
		return (ft_putstr_fd("Error\nError with color values\n", 2), 0);
	colors->b = ft_atoi(rgb[2]);
	if (colors->b == 0 && *rgb[2] != '0')
		return (ft_putstr_fd("Error\nError with color values\n", 2), 0);
	if (colors->r > 255 || colors->r < 0 || colors->g > 255 || \
		colors->g < 0 || colors->b > 255 || colors->b < 0)
		return (ft_putstr_fd("Error\nColor out of range\n", 2), 0);
	return (1);
}
