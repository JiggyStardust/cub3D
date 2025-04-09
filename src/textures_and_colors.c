/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_and_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:47:10 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/08 16:15:26 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_textures(t_data *data)
{
	data->textures.no = mlx_load_png(data->map_info.no);
	if (!data->textures.no && free_textures(data, 0))
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	data->textures.so = mlx_load_png(data->map_info.so);
	if (!data->textures.so && free_textures(data, 1))
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	data->textures.we = mlx_load_png(data->map_info.we);
	if (!data->textures.we && free_textures(data, 2))
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	data->textures.ea = mlx_load_png(data->map_info.ea);
	if (!data->textures.ea && free_textures(data, 3))
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	free_textures(data, 0);
	return (1);
}

int	get_color(char **info, t_data *data)
{
	char	**rgb;

	if (!info[1] || info[2])
		return (ft_putstr_fd("Error\nInvalid identifier or" \
		" missing color\n", 2), 0);
	rgb = ft_split(info[1], ',');
	if (!rgb)
		return (ft_putstr_fd("Error\nAllocation failed\n", 2), 0);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_putstr_fd("Error\nError with color value\n", 2);
		return (free_2d_array(rgb), 0);
	}
	if (!ft_strncmp(info[0], "F", 2) || !ft_strncmp(info[0], "C\n", 3))
	{
		if (!set_color(rgb, &data->map_info.floor_color))
			return (free_2d_array(rgb), 0);
	}
	else if (!ft_strncmp(info[0], "C", 2) || !ft_strncmp(info[0], "C\n", 3))
	{
		if (!set_color(rgb, &data->map_info.ceiling_color))
			return (free_2d_array(rgb), 0);
	}
	free_2d_array(rgb);
	return (1);
}

int	textures(char **info, t_data *data)
{
	char	**texture;

	if (info[1] == NULL)
		return (ft_putstr_fd("Error\nInvalid identifier or" \
		" missing texture\n", 2), 0);
	if (info[2])
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), 0);
	texture = ft_split(info[1], '\n');
	if (!texture && ft_strncmp(info[0], "\n", 2))
		return (0);
	if (!ft_strncmp(info[0], "NO", 3) && \
		!add_texture(texture[0], &data->map_info.no))
		return (ft_free_array(&texture), 0);
	else if (!ft_strncmp(info[0], "SO", 3) && \
		!add_texture(texture[0], &data->map_info.so))
		return (ft_free_array(&texture), 0);
	else if (!ft_strncmp(info[0], "EA", 3) && \
		!add_texture(texture[0], &data->map_info.ea))
		return (ft_free_array(&texture), 0);
	else if (!ft_strncmp(info[0], "WE", 3) && \
		!add_texture(texture[0], &data->map_info.we))
		return (ft_free_array(&texture), 0);
	ft_free_array(&texture);
	return (1);
}

int	color_texture_loop(t_data *data, char *line)
{
	char	**info;
	char	c;

	info = ft_split(line, ' ');
	free(line);
	if (!info)
		return (ft_putstr_fd("Error\nAllocation failed\n", 2), 0);
	c = info[0][0];
	if (c == 'F' || c == 'C')
	{
		if (!get_color(info, data))
			return (free_2d_array(info), 0);
	}
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (!textures(info, data))
			return (free_2d_array(info), 0);
	}
	return (free_2d_array(info), 1);
}

int	get_texture_and_color(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(data->file, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nOpening of file failed\n", 2), 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!color_texture_loop(data, line))
		{
			read_to_end(fd);
			return (close(fd), 0);
		}
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (!all_found(data))
		return (0);
	return (1);
}
