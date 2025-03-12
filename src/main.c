/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/12 19:55:49 by sniemela         ###   ########.fr       */
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

mlx_image_t	*raycaster(t_data *data)
{
	t_ray 		ray;
	int			xy;
	float		map_x;
	float		map_y;
	int			i;
	mlx_image_t *img;

	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ray.x = data->player.x;
	ray.y = data->player.y;
	ray.angle = data->player.angle - (33.0 / 180 * PI);
	if (ray.angle == 2 * PI)
		ray.angle = 0;
	else if (ray.angle < 0)
		ray.angle += 2 * PI;
	i = 0;
	while (i < WIDTH)
	{
		map_x = ray.x;
		map_y = ray.y;
		xy = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(data->player.y), 1);
		while (data->map[xy] == FLOOR)
		{
			map_x -= cos(ray.angle);
			map_y -= sin(ray.angle);
			xy = get_index_of_rov_and_col(data, (int)map_x, (int)map_y, 1);
		}
		ray.dx = fabsf(map_x - ray.x);
		ray.dy = fabsf(map_y - ray.y);
		ray.len = sqrt(pow(ray.dx, 2) + pow(ray.dy, 2)) * cos(PI / 2 - ray.angle);
		draw_ray(data, ray, i, img);
		ray.angle += (1.0/180 * PI);
		if (ray.angle == 2 * PI)
			ray.angle = 0;
		i += WIDTH / 66;
	}
	return (img);
}

mlx_image_t *draw_ray(t_data *data, t_ray ray, int i, mlx_image_t *img)
{

	float	center;
	int		wall_height;
	int		y;
	int		x;
	(void)data;

	center = HEIGHT / 2;
	wall_height = HEIGHT / ray.len;
	x = 0;
	while (x < WIDTH / 66)
	{
		y = center - wall_height / 2;
		while (y <= center + wall_height / 2)
		{
			mlx_put_pixel(img, i + x, y, RED);
			y++;
		}
		x++;
	}
	return (img);
}

int	main(int argc, char **argv)
{
	t_data	data;
	mlx_image_t *rimg;

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
	rimg = raycaster(&data);
	if (!images_to_window(&data, rimg))
		terminate_free(&data, 1, "Error\nProblem with opening the window.\n");
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &movement, &data);
	mlx_close_hook(data.mlx, &close_window, &data);
	mlx_loop(data.mlx);
	cleanup(&data);
	terminate_free(&data, 0, NULL);
	return (0);
}
