/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:25:15 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/24 16:48:31 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	textures(char **info, t_data *data)
{
	if (!ft_strncmp(info[0], "NO", 3))
	{
		data->map_info.NO = ft_strdup(info[1]);
		if (!data->map_info.NO)
			return (0);
	}
	else if (!ft_strncmp(info[0], "SO", 3))
	{
		data->map_info.SO = ft_strdup(info[1]);
		if (!data->map_info.SO)
			return (0);
	}
	else if (!ft_strncmp(info[0], "EA", 3))
	{
		data->map_info.EA = ft_strdup(info[1]);
		if (!data->map_info.EA)
			return (0);
	}
	else if (!ft_strncmp(info[0], "WE", 3))
	{
		data->map_info.WE = ft_strdup(info[1]);
		if (!data->map_info.WE)
			return (0);
	}
	return (1);
}

int	get_color(char **info, t_data *data)
{
	char	**rgb;

	rgb = ft_split(info[1], ',');
	if (!rgb)
		return (0);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_2d_array(rgb), 0);
	if (*info[0] == 'F')
	{
		data->map_info.floor_color.r = ft_atoi(rgb[0]);
		data->map_info.floor_color.g = ft_atoi(rgb[1]);
		data->map_info.floor_color.b = ft_atoi(rgb[2]);
	}
	else if (*info[0] == 'C')
	{
		data->map_info.ceiling_color.r = ft_atoi(rgb[0]);
		data->map_info.ceiling_color.g = ft_atoi(rgb[1]);
		data->map_info.ceiling_color.b = ft_atoi(rgb[2]);
	}
	return (1);
}

int	get_texture_and_color(t_data *data)
{
	int	fd;
	char	*line;
	char	**info;

	fd = open(data->file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		info = ft_split(line, ' ');
		free(line);
		if (!info)
			return (0);
		if (!ft_strncmp(info[0], "F", 2) || !ft_strncmp(info[0], "C", 2))
		{
			if (!get_color(info, data))
				return (free_2d_array(info), 0);
		}
		else
		{
			if (!textures(info, data))
				return (free_2d_array(info), 0);
		}
		free_2d_array(info);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	get_map_size(t_data *data)
{
	int	i;
	int	j;
	int	fd;
	char	*line;

	i = 0;
	fd = open(data->file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		if (line[j] == 'N' || line[j] == 'W' || line[j] == 'S' || line[j] == 'E' || line[j] == 'F' || line[j] == 'C' || line[j] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		while (line[j] != '\n')
			j++;
		if (j > data->map_info.width)
			data->map_info.width = j;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	data->map_info.height = i;
	return (1);
}

static int	check_file_format(char *file)
{
	//if ending is not .cub, file is in wrong format
	int		i;

	i = ft_strlen(file) - 4;
	if (i < 0)
		return (0);
	file += i;
	if (ft_strncmp(file, ".cub", 5))
		return (0);
	return (1);
}

#include <stdio.h>

int	parsing(t_data *data, char **argv)
{
	//check file name is in .cub format
	if (!check_file_format(argv[1]))
		return (0);
	data->file = argv[1];
	if (!get_map_size(data))
		return (0);
	if (!get_texture_and_color(data))
		return (0);
	printf("north: %s\n", data->map_info.NO);
	printf("south: %s\n", data->map_info.SO);
	printf("west: %s\n", data->map_info.WE);
	printf("east: %s\n", data->map_info.EA);
	printf("height: %d\n", data->map_info.height);
	printf("width: %d\n", data->map_info.width);
	//check if map is valid
	return (1);
}
