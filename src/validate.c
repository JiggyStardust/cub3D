/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>         #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:21:08 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/10 10:51:11 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	permission_denied(char *file)
{
	ft_putstr_fd("No permission to file or file doesn't exist <", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(">\n", 2);
}

int	access_textures(t_map map)
{
	int	fd;

	fd = open(map.NO, O_RDONLY);
	if (fd < 0)
		return (permission_denied(map.NO), 0);
	close(fd);
	fd = open(map.SO, O_RDONLY);
	if (fd < 0)
		return (permission_denied(map.SO), 0);
	close(fd);
	fd = open(map.WE, O_RDONLY);
	if (fd < 0)
		return (permission_denied(map.WE), 0);
	fd = open(map.EA, O_RDONLY);
	if (fd < 0)
		return (permission_denied(map.EA), 0);
	return (1);
}

//FLOOR -> WALL and FLOOR
//WALL -> anything is ok
//PADDING -> wall and padding is ok

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

int valid_map2(enum e_type *map, int width, int height)
{
	int	i;

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

int	load_textures(t_data *data)
{
	data->textures.NO = mlx_load_png(data->map_info.NO);
	if (!data->textures.NO)
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	data->textures.SO = mlx_load_png(data->map_info.SO);
	if (!data->textures.SO)
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	data->textures.WE = mlx_load_png(data->map_info.WE);
	if (!data->textures.WE)
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	data->textures.EA = mlx_load_png(data->map_info.EA);
	if (!data->textures.EA)
		return (ft_putstr_fd("Error\nLoading textures failed\n", 2), 0);
	return (1);
}

int	is_valid(t_data *data)
{
	//if a texture is missing //checked
	//if duplicates in textures and colors -> return 0 //checked
	//if can't open textures -> return 0 //checked
	if (!data->player.found)
		return (ft_putstr_fd("Player missing\n", 2), 0);
	if (!check_file_format(data->map_info.NO, ".png"))
		return (0);
	if (!check_file_format(data->map_info.SO, ".png"))
		return (0);
	if (!check_file_format(data->map_info.WE, ".png"))
		return (0);
	if (!check_file_format(data->map_info.EA, ".png"))
		return (0);
	if (!access_textures(data->map_info))
		return (0);
	if (!valid_map2(data->map, data->map_info.width, data->map_info.height))
		return (ft_putstr_fd("Invalid map\n", 2), 0);
	if (!load_textures(data))
		return (0);
	//if texture files are .png //checked
	//if wall is missing -> return 0 //checked
	//if player is missing -> return 0 //checked
	//if other characters than 01NSEW -> return 0 //checked
	//if colors are in the range (0 - 255 or something like that) //checked
	//if player is in the map twice //checked
	//no newline at the end of map //checked
	return (1);
}
