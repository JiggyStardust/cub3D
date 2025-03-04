/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/04 12:21:01 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	data->map_info.height = 0;
	data->map_info.width = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	//check if map is valid and parse
	if (argc != 2)
		return (ft_putstr_fd("Example: ./cub3D file.cub\n", 2), 1);
	init_data(&data);
	if (!parsing(&data, argv))
		return (ft_putstr_fd("Example: ./cub3D file.cub\n", 2), 1);
	//create the window
	//draw the image
	//put image to window
	//free everything
	return (0);
}