/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:21:08 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/10 09:37:40 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	permission_denied(char *file)
{
	ft_putstr_fd("Error\nNo permission to file or file doesn't exist <", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(">\n", 2);
}

int	access_textures(t_data *data)
{
	int	fd;

	fd = open(data->map_info.no, O_RDONLY);
	if (fd < 0)
		return (permission_denied(data->map_info.no), 0);
	close(fd);
	fd = open(data->map_info.so, O_RDONLY);
	if (fd < 0)
		return (permission_denied(data->map_info.so), 0);
	close(fd);
	fd = open(data->map_info.we, O_RDONLY);
	if (fd < 0)
		return (permission_denied(data->map_info.we), 0);
	close(fd);
	fd = open(data->map_info.ea, O_RDONLY);
	if (fd < 0)
		return (permission_denied(data->map_info.ea), 0);
	close(fd);
	return (1);
}

int	check_type(enum e_type cur_type, enum e_type pre_type)
{
	if (pre_type == FLOOR)
	{
		if (cur_type == PADDING)
			return (0);
	}
	if (pre_type == PADDING)
	{
		if (cur_type == FLOOR)
			return (0);
	}
	return (1);
}

int	valid_map(enum e_type *map, int width, int height)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if ((i == 0 || i == height - 1) && map[i * width + j] == FLOOR)
				return (0);
			if ((j == 0 || j == width -1) && map[i * width + j] == FLOOR)
				return (0);
		}
	}
	i = -1;
	while (++i < width * height)
	{
		if ((i + 1) < (width * height) && !check_type(map[i], map[i + 1]))
			return (0);
		if (i < (width * (height - 1)) && !check_type(map[i], map[i + width]))
			return (0);
	}
	return (1);
}

int	is_valid(t_data *data)
{
	if (!data->player.found)
		return (ft_putstr_fd("Error\nPlayer missing\n", 2), 0);
	if (!check_file_format(data->map_info.no, ".png"))
		return (0);
	if (!check_file_format(data->map_info.so, ".png"))
		return (0);
	if (!check_file_format(data->map_info.we, ".png"))
		return (0);
	if (!check_file_format(data->map_info.ea, ".png"))
		return (0);
	if (!access_textures(data))
		return (0);
	if (!valid_map(data->map, data->map_info.width, data->map_info.height))
		return (ft_putstr_fd("Error\nInvalid map\n", 2), 0);
	if (!load_textures(data))
		return (0);
	return (1);
}
