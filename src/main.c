/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/09 09:52:40 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	init_data(t_data *data)
{
	data->map_info.height = 0;
	data->map_info.width = 0;
	data->map_info.no = NULL;
	data->map_info.so = NULL;
	data->map_info.we = NULL;
	data->map_info.ea = NULL;
	data->map_info.floor_color.found = 0;
	data->map_info.ceiling_color.found = 0;
	data->map = NULL;
	data->player.found = 0;
	data->view = NULL;
	data->ray = NULL;
	data->minimap = NULL;
}

static void	init_player(t_data *data)
{
	data->player.angle = get_player_angle(data->player.p_dir);
	data->player.d_x = cos(data->player.angle) * MOVE_SPEED;
	data->player.d_y = sin(data->player.angle) * MOVE_SPEED;
	data->player.d_lr_x = cos(data->player.angle + PI / 2) * MOVE_SPEED;
	data->player.d_lr_y = sin(data->player.angle + PI / 2) * MOVE_SPEED;
}

static void	loops(t_data *data)
{
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_loop_hook(data->mlx, &movement, data);
	mlx_close_hook(data->mlx, &close_window, data);
	mlx_loop(data->mlx);
}

void	cleanup(t_data *data)
{
	if (data->map)
		free(data->map);
	if (data->map_info.no)
		free(data->map_info.no);
	if (data->map_info.so)
		free(data->map_info.so);
	if (data->map_info.we)
		free(data->map_info.we);
	if (data->map_info.ea)
		free(data->map_info.ea);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Error\nExample: ./cub3D file.cub\n", 2), 1);
	init_data(&data);
	if (!parsing(&data, argv))
	{
		cleanup(&data);
		return (1);
	}
	init_player(&data);
	data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!data.mlx)
		return (false);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	if (!setup_images(&data))
		terminate_free(&data, 1, "Error\nProblem with setup_images.\n");
	data.view = raycaster(&data);
	if (!images_to_window(&data))
		terminate_free(&data, 1, "Error\nProblem with opening the window.\n");
	loops(&data);
	terminate_free(&data, 0, NULL);
	return (0);
}
