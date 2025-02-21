/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:25:15 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/21 16:03:13 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	textures(char **info)
{
	if (!ft_strncmp(info[0], "NO", 3))
		//data->map_info.NO
	else if (!ft_strncmp(info[0], "SO", 3))
		//data->map_info.SO
	else if (!ft_strncmp(ino[0], "EA", 3))
		//data->map_info.EA
	else if (!ft_strncmp(info[0], "WE", 3))
		//data->map_info.WE
	else
		return (1);
	//texture is in this form: NO ./path_to_the_north_texture
	//and we want: ./path_to_the_north_texture
}

void	get_color(char **info, t_data *data)
{
}

void	get_texture_and_color(t_data *data)
{
	int	fd;
	int	i;
	char	*line;
	char	**info;

	fd = open(data->file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		info = ft_split(line, ' ');
		if (!info)
			return (0);
		if (!ft_strncmp(info[0], "F", 2) || !ft_strncmp(info[0], "C", 2))
			get_color(info, data);
		else
			textures(info, data);
		free(line);
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
	if (!get_texture_and_color(&data->map_info))
		return (0);
	//check if map is valid
	return (1);
}
