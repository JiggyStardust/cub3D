#include "../includes/cub3d.h"

void	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	terminate_free(data, 0, NULL);
	exit(0);
}

void	move_player(t_data *data)
{
	float	move_speed = 0.1;
	float	turn_speed = 0.1;
	float	x;
	float	y;

	// printf("p_y: %f, p_x: %f, p_a: %f\n", data->p_y, data->p_x, data->p_a);

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		x = data->p_x - data->p_d_x * move_speed;
		y = data->p_y - data->p_d_y * move_speed;

		if (data->map[(int)y][(int)data->p_x] != '1')
			data->p_y = y;
		if (data->map[(int)data->p_y][(int)x] != '1')
			data->p_x = x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		x = data->p_x + data->p_d_x * move_speed;
		y = data->p_y + data->p_d_y * move_speed;

		if (data->map[(int)y][(int)data->p_x] != '1')
			data->p_y = y;
		if (data->map[(int)data->p_y][(int)x] != '1')
			data->p_x = x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->p_a -= turn_speed;
		if (data->p_a < 0)
			data->p_a += 2 * PI;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->p_a += turn_speed;
		if (data->p_a > 2 * PI)
			data->p_a -= 2 * PI;
	}
	data->p_d_x = cos(data->p_a) * move_speed;
	data->p_d_y = sin(data->p_a) * move_speed;
}

void	move_player_image(t_data *data)
{
	data->p_img->instances[0].x = data->p_x * TILE_MINI;
	data->p_img->instances[0].y = data->p_y * TILE_MINI;
}


// void draw_player(t_data *data) // Using mlx_put_pixel and mlx_image_to_window
// {
// 	int center_x = TILE_MINI / 2;
// 	int center_y = TILE_MINI / 2;
// 	int	y;
// 	int	x;

// 	mlx_delete_image(data->mlx, data->p_img);
// 	data->p_img = mlx_new_image(data->mlx, TILE_MINI, TILE_MINI);
// 	y = -6;
// 	while (y <= 6)
// 	{
// 		x = -6;
// 		while (x <= 6)
// 		{
// 			mlx_put_pixel(data->p_img, center_x + x, center_y + y, 0xFF0000FF);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_image_to_window(data->mlx, data->p_img, data->p_x * TILE_MINI, data->p_y * TILE_MINI);
// }

void	movement(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	move_player(data);
	move_player_image(data); // moving player pixture using instances
	//draw_player(data); // using mlx_put_pixel
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		terminate_free(data, 0, NULL);
	/* 
		Shooting, opening doors etc might come here aswell
	*/
}

// bool	init_cubed(t_data *data, char *path_to_map)
// {
	// data->map = create_map(path_to_map);
	// data->m_height = get_height(data->map);
	// data->m_width = get_width(data->map);
	// data->mlx = mlx_init(data->m_width, data->m_height, "minimap", true);
	// if (!data->mlx)
	// 	return (false);
	// mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	// data->p_dir = get_player_dir(data->map);

	// data->p_a = get_player_angle(data->p_dir);
	// data->p_y = get_player_y(data->map, data->p_dir);
	// data->p_x = get_player_x(data->map, data->p_y, data->p_dir);
	// return (true);
// }

// int main(int ac, char **av)
// {
// 	t_data	data;

// 	if (ac != 2)
// 		return (1);
// 	if (!init_cubed(&data, av[1]))
// 		return (1);
// 	if (!setup_images(&data))
// 		terminate_free(&data, 1, "Error\nProblem with setup_images.\n");
// 	if (!images_to_window(&data))
// 		terminate_free(&data, 1, "Error\nProblem with opening the window.\n");
// 	mlx_key_hook(data.mlx, &key_hook, &data);
// 	mlx_loop_hook(data.mlx, &movement, &data);
// 	mlx_close_hook(data.mlx, &close_window, &data);
// 	mlx_loop(data.mlx);
// 	terminate_free(&data, 0, NULL);
// }
