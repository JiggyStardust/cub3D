/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/08 15:32:06 by sniemela         ###   ########.fr       */
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
	data->view = NULL;
	data->ray = NULL;
	data->minimap = NULL;
}

void	init_player(t_data *data)
{
	data->player.angle = get_player_angle(data->player.p_dir);
	data->player.d_x = cos(data->player.angle) * MOVE_SPEED;
	data->player.d_y = sin(data->player.angle) * MOVE_SPEED;
	data->player.d_lr_x = cos(data->player.angle + PI / 2) * MOVE_SPEED;
	data->player.d_lr_y = sin(data->player.angle + PI / 2) * MOVE_SPEED;
}

void	cleanup(t_data *data)
{
	if (data->map)
		free(data->map);
	if (data->map_info.NO)
		free(data->map_info.NO);
	if (data->textures.NO)
		mlx_delete_texture(data->textures.NO);
	if (data->map_info.SO)
		free(data->map_info.SO);
	if (data->textures.SO)
		mlx_delete_texture(data->textures.SO);
	if (data->map_info.WE)
		free(data->map_info.WE);
	if (data->textures.WE)
		mlx_delete_texture(data->textures.WE);
	if (data->map_info.EA)
		free(data->map_info.EA);
	if (data->textures.EA)
		mlx_delete_texture(data->textures.EA);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Example: ./cub3D file.cub\n", 2), 1);
	init_data(&data);
	if (!parsing(&data, argv))
		return (cleanup(&data), 1);
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
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &movement, &data);
	mlx_close_hook(data.mlx, &close_window, &data);
	mlx_loop(data.mlx);
	cleanup(&data);
	terminate_free(&data, 0, NULL);
	return (0);
}
