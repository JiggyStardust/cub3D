/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/07 17:41:37 by sniemela         ###   ########.fr       */
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
}

void	cleanup(t_data *data)
{
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

void get_pixel(mlx_texture_t *texture, uint32_t *color, int xy)
{
	t_rgb rgb;
	
	if (xy + 3 >= (texture->width * texture->height))
		return ;
	rgb.r = texture->pixels[xy * 4];
	rgb.g = texture->pixels[xy * 4 + 1];
	rgb.b = texture->pixels[xy * 4 + 2];
	rgb.a = texture->pixels[xy * 4 + 3];
	*color = (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

void	choose_texture(t_data *data, t_ray ray)
{
	if (ray.side == VERTICAL)
	{
		if (cos(ray.angle) > 0)
			data->texture = data->textures.EA;
		else
			data->texture = data->textures.WE;
	}
	else
	{
		if (sin(ray.angle) < 0)
			data->texture = data->textures.NO;
		else
			data->texture = data->textures.SO;
	}
}

uint32_t get_x(t_data *data, t_ray ray)
{
	int			t_x;
	double		x;

	if (ray.side == VERTICAL)
		x = ray.y + ray.len2 * sin(ray.angle);
	else
		x = ray.x + ray.len2 * cos(ray.angle);
	x -= floor((x));
	t_x = x * (double)data->texture->width;
	if ((ray.side == VERTICAL && cos(ray.angle) > 0) || (ray.side == HORIZONTAL && sin(ray.angle) < 0))
		t_x = data->texture->width - t_x - 1;
	if (t_x < 0)
		t_x = 0;
	if (t_x >= data->texture->width)
		t_x = data->texture->width - 1;
	return ((uint32_t)t_x);
}

mlx_image_t *draw_ray(t_data *data, t_ray ray, int x, mlx_image_t *img)
{

	float	wall_height;
	int		wall_top;
	double	t_pos;
	uint32_t	text_x;
	uint32_t	text_y;
	double	step;
	uint32_t	color;

	wall_height = HEIGHT / ray.len;
	wall_top = (HEIGHT / 2) - wall_height / 2;
	if (wall_top < 0)
		wall_top = 0;
	choose_texture(data, ray);
	text_x = get_x(data, ray);
	step = (double) data->texture->height / wall_height;
	t_pos = (wall_top - HEIGHT / 2 + wall_height / 2) * step;
	while (wall_top <= (HEIGHT / 2) + wall_height / 2)
	{
		text_y = (uint32_t) t_pos;
		if (text_y < 0)
			text_y = 0;
		if (text_y >= data->texture->height)
			text_y = (uint32_t) data->texture->height - 1;
		get_pixel(data->texture, &color, (data->texture->width * text_y + text_x));
		mlx_put_pixel(img, x, wall_top, color);
		t_pos += step;
		wall_top++;
		if (wall_top == HEIGHT)
			break ;
	}
	return (img);
}

int	main(int argc, char **argv)
{
	t_data	data;

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
	data.player.d_x = cos(data.player.angle) * MOVE_SPEED;
	data.player.d_y = sin(data.player.angle) * MOVE_SPEED;
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
