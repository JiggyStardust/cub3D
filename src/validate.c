/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>         #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:21:08 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/06 18:34:22 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	access_textures(t_map map)
{
	int	fd;

	fd = open(map.NO, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(map.SO, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(map.WE, O_RDONLY);
	if (fd < 0)
		return (0);
	fd = open(map.EA, O_RDONLY);
	if (fd < 0)
		return (0);
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

int	check_box(int i, t_data *data, enum e_type type)
{
	//i++, i--, i+width, i-width
	t_position	pos;
	
	pos = get_pos(data, i);
	//checks the outer edges
	if (pos.col == data->map_info.width - 1 && pos.row == data->map_info.height - 1)
		return (1);
	if ((pos.col == 0 || pos.row == 0) && (data->map[i] != PADDING && data->map[i] != WALL))
		return (0);
	if ((pos.col == data->map_info.width - 1 || pos.row == data->map_info.height - 1) && (data->map[i] != PADDING && data->map[i] != WALL))
		return (0);
	if (!check_type(data->map[i], type))
		return (0);
	//box above
	//if (pos.row > 0)
	//{
	//	if (!check_box((i - data->map_info.width), data, data->map[i]))
	//		return (0);
	//}
	//box on the left
	//if (pos.col > 0)
	//{
	//	if (!check_box((i - 1), data, data->map[i]))
	//		return (0);
	//}
	//box on the right
	if (pos.col < data->map_info.width - 1)
	{
		if (!check_box((i + 1), data, data->map[i]))
			return (0);
	}
	//box below
	if (pos.row < data->map_info.height - 1)
	{
		if (!check_box((i + data->map_info.width), data, data->map[i]))
			return (0);
	}
	return (1);
}

int	valid_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map[i] != WALL && data->map[i] != PADDING)
		return (0);
	//recursively check each box
	//box on the right
	if (!check_box((i + 1), data, data->map[i]))
		return (0);
	//box below
	if (!check_box((i + data->map_info.width), data, data->map[i]))
		return (0);
	return (1);
}

int	is_valid(t_data *data)
{
	//if a texture is missing //checked
	//if duplicates in textures and colors -> return 0 //checked
	//if can't open textures -> return 0 //checked
	if (!access_textures(data->map_info))
		return (0);
	if (!valid_map(data))
		return (0);
	//if texture files are .png
	//if wall is missing -> return 0 //checked
	//if player is missing -> return 0 //checked
	//if other characters than 01NSEW -> return 0 //checked
	//if colors are in the range (0 - 255 or something like that)
	return (1);
}
