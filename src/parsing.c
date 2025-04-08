/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:25:15 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/10 12:07:24 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	read_to_end(int fd)
{
	char	*line;

	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	all_found(t_data *data)
{
	if (!data->map_info.NO)
		return (ft_putstr_fd("All textures not found", 2), 0);
	if (!data->map_info.SO)
		return (ft_putstr_fd("All textures not found", 2), 0);
	if (!data->map_info.EA)
		return (ft_putstr_fd("All textures not found", 2), 0);
	if (!data->map_info.WE)
		return (ft_putstr_fd("All textures not found", 2), 0);
	if (!data->map_info.floor_color.found)
		return (ft_putstr_fd("All textures not found", 2), 0);
	if (!data->map_info.ceiling_color.found)
		return (ft_putstr_fd("All textures not found", 2), 0);
	return (1);
}

int	check_file_format(char *file, char *format)
{
	int		i;

	i = ft_strlen(file) - 4;
	if (i < 0)
	{
		ft_putstr_fd("Expected file format: ", 2);
		ft_putstr_fd(format, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	file += i;
	if (ft_strncmp(file, format, 5))
	{	
		ft_putstr_fd("Expected file format: ", 2);
		ft_putstr_fd(format, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

int	parsing(t_data *data, char **argv)
{
	if (!check_file_format(argv[1], ".cub"))
		return (0);
	data->file = argv[1];
	if (!get_map_size(data))
		return (0);
	if (!get_texture_and_color(data))
		return (0);
	if (!get_map(data))
		return (0);
	if (!is_valid(data))
		return (0);
	return (1);
}

/*
void	draw_map(t_data *data)
{
	int	i;
	int	j;
	int	h;

	i = -1;
	j = -1;
	while (++i < data->map_info.height)
	{
		h = -1;
		while (++h < data->map_info.width)
			printf("%d", data->map[++j]);
		printf("\n");
	}
}*/
