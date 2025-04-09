/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:40:59 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/08 09:44:50 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_map_size(t_data *data)
{
	int		j;
	int		fd;
	char	*line;

	fd = open(data->file, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nOpening of file failed\n", 2), 0);
	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		if (is_texture_or_color(line, data->map_info.width))
		{
			line = get_next_line(fd);
			continue ;
		}
		while (line[j] && line[j] != '\n')
			j++;
		if (j > data->map_info.width)
			data->map_info.width = j;
		free(line);
		line = get_next_line(fd);
		data->map_info.height++;
	}
	return (close(fd), 1);
}

int	add_padding(t_data *data, int i, int j)
{
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

int	to_map(t_data *data, char *line, int j, int i)
{
	while (line[++i])
	{
		if (line[i] != '\n')
		{
			if (line[i] == '0')
				data->map[j++] = FLOOR;
			else if (line[i] == '1')
				data->map[j++] = WALL;
			else if (line[i] == 'N' || line[i] == 'S' || \
				line[i] == 'W' || line[i] == 'E')
			{
				if (!data->player.found)
					data->player = player(line[i], j++, data);
				else
					return (ft_putstr_fd("Error\nMultiple players\n", 2), -1);
			}
			else if (line[i] == ' ' || line[i] == '\0' || i == '\n')
				data->map[j++] = PADDING;
			else
				return (-1);
		}
		else
			break ;
	}
	return (add_padding(data, i, j));
}

int	get_line(t_data *data, char *line, int j)
{
	int	i;

	i = 0;
	if (is_texture_or_color(line, j))
	{
		if (j > 0)
		{
			ft_putstr_fd("Error\nTextures and colors in wrong place\n", 2);
			return (-1);
		}
		return (j);
	}
	j = to_map(data, line, j, -1);
	free(line);
	if (j < 0)
		return (ft_putstr_fd("Error\nInvalid character in file\n", 2), -1);
	return (j);
}

int	get_map(t_data *data)
{
	int		fd;
	char	*line;
	int		j;

	data->map = malloc(sizeof(enum e_type) * \
		(data->map_info.height * data->map_info.width + 1));
	if (!data->map)
		return (ft_putstr_fd("Error\nAllocation failed\n", 2), 0);
	fd = open(data->file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nOpening of file failed\n", 2), 0);
	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		j = get_line(data, line, j);
		if (j < 0)
		{
			read_to_end(fd);
			return (close(fd), 0);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
