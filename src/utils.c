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
// #include <stdio.h>
// enum e_type	get_type(t_data *data, int row, int col)
// {
// 	//return what type is in pos
// 	int	i;

// 	i = ((row - 1) * data->map_info.width) + col - 1;
// 	printf("i: %d\n", i);
// 	return (data->map[i]);
// }

t_position	get_pos(t_data *data, int i)
{
	t_position	pos;
	int	row;
	int col;
	
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
	return (player);
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
			{
				if (!data->player.found)
				{
					data->player = player(line[i], j, data);
					data->player.found = 1;
				}
				else
					return (ft_putstr_fd("Player in map multiple times\n", 2), 0);
				data->map[j++] = FLOOR; 
			}
			else if (line[i] == ' ' || line[i] == '\0')
				data->map[j++] = PADDING;
			else
				return (-1);
		}
		else
			break ;
		i++;
	}
	if (i < data->map_info.width)
	{
		while (i < data->map_info.width)
		{
			data->map[j++] = PADDING;
			i++;
		}
	}
	return (j);
}
