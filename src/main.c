/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/10 16:28:23 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_data(t_data *data)
{
	data->map_info.height = 0;
	data->map_info.width = 0;
	data->map_info.NO = NULL;
	data->map_info.SO = NULL;
	data->map_info.WE = NULL;
	data->map_info.EA = NULL;
	data->map_info.floor_color.found = 0;
	data->map_info.ceiling_color.found = 0;
	data->map = NULL;
	data->player.found = 0;
}

void	cleanup(t_data *data)
{
	//if (data->file)
		//free(data->file);
	if (data->map)
		free(data->map);
	if (data->map_info.NO)
		free(data->map_info.NO);
	if (data->map_info.SO)
		free(data->map_info.SO);
	if (data->map_info.WE)
		free(data->map_info.WE);
	if (data->map_info.EA)
		free(data->map_info.EA);
}

void	raycaster(t_data *data)
{
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float 	camera_x;
	float	ray_dir_x;
	float 	ray_dir_y;
	int		map

	if (data->player.p_dir == 'N')
	{
		dir_x = 0;
		dir_y = -1;
		plane_x = 0.66;
		plane_y = 0;
	}
	if (data->player.p_dir == 'S')
	{
		dir_x = 0;
		dir_y = 1;
		plane_x = 0.66;
		plane_y = 0;
	}
	if (data->player.p_dir == 'W')
	{
		dir_x = -1;
		dir_y = 0;
		plane_x = 0;
		plane_y = 0.66;
	}
	if (data->player.p_dir == 'E')
	{
		dir_x = 1;
		dir_y = 0;
		plane_x = 0;
		plane_y = 0,66;
	}
	for(int x = 0; x < WIDTH; x++)
    {
      camera_x = 2 * x / (float)WIDTH - 1; //x-coordinate in camera space
      ray_dir_x = dir_x + plane_x * camera_x;
      ray_dir_y = dir_y + plane_y * camera_x;

	}

}

int	main(int argc, char **argv)
{
	t_data	data;

	//check if map is valid and parse
	if (argc != 2)
		return (ft_putstr_fd("Example: ./cub3D file.cub\n", 2), 1);
	init_data(&data);
	if (!parsing(&data, argv))
		return (cleanup(&data), 1);
	data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!data.mlx)
		return (false);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	data.player.angle = get_player_angle(data.player.p_dir);
	if (!setup_images(&data))
		terminate_free(&data, 1, "Error\nProblem with setup_images.\n");
	raycaster(&data);
	if (!images_to_window(&data))
		terminate_free(&data, 1, "Error\nProblem with opening the window.\n");
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &movement, &data);
	mlx_close_hook(data.mlx, &close_window, &data);
	mlx_loop(data.mlx);
	cleanup(&data);
	terminate_free(&data, 0, NULL);
	return (0);
}
