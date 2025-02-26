/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:46:53 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/26 16:03:16 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_2d_array(char **ptr)
{
	int	i;

	i = -1;
	while (ptr && ptr[++i])
		free(ptr[i]);
	free(ptr);
}
#include <stdio.h>
enum e_type	get_type(t_data *data, int row, int col)
{
	//return what type is in pos
	int	i;

	i = ((row - 1) * data->map_info.width) + col - 1;
	printf("i: %d\n", i);
	return (data->map[i]);
}

t_position	get_pos(t_data *data, int i)
{
	t_position	pos;
	int	row;
	int col;
	
	pos.row = 0;
	row = 0;
	while (row < i)
	{
		pos.row++;
		row += data->map_info.width;
	}
	pos.col = 0;
	col = (pos.row - 1) * data->map_info.width;
	while (col++ <= i)
		pos.col++;
	return (pos);
}

enum e_type	player(char c)
{
	if (c == 'N')
		return (N);
	if (c == 'S')
		return (S);
	if (c == 'W')
		return (W);
	if (c == 'E')
		return (E);
	return (0);
}

int	to_map(t_data *data, char *line, int j)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\n')
		{
			if (line[i] == '0')
				data->map[j++] = FLOOR;
			else if (line[i] == '1')
				data->map[j++] = WALL;
			else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
				data->map[j++] = player(line[i]);
			else
				data->map[j++] = PADDING;
		}
		else if (i < data->map_info.width)
		{
			while (i < data->map_info.width)
			{
				data->map[j++] = PADDING;
				i++;
			}
		}
		i++;
	}
	return (j);
}
