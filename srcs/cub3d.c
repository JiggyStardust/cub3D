#include "../cub3d.h"

void	close_window(void *param)
{
	t_cubed	*cubed;

	cubed = (t_cubed *)param;
	terminate_free(cubed, 0, NULL);
	exit(0);
}

void	move_player(t_cubed *cubed)
{
	float	move_speed = 0.1;
	float	turn_speed = 0.1;
	float	x;
	float	y;

	printf("p_y: %f, p_x: %f\n", cubed->p_y, cubed->p_x);

	if (mlx_is_key_down(cubed->mlx, MLX_KEY_W))
	{
		x = cubed->p_x - cubed->p_d_x * move_speed;
		y = cubed->p_y - cubed->p_d_y * move_speed;

		if (cubed->map[(int)y][(int)cubed->p_x] != '1')
			cubed->p_y = y;
		if (cubed->map[(int)cubed->p_y][(int)x] != '1')
			cubed->p_x = x;
	}
	if (mlx_is_key_down(cubed->mlx, MLX_KEY_S))
	{
		x = cubed->p_x + cubed->p_d_x * move_speed;
		y = cubed->p_y + cubed->p_d_y * move_speed;

		if (cubed->map[(int)y][(int)cubed->p_x] != '1')
			cubed->p_y = y;
		if (cubed->map[(int)cubed->p_y][(int)x] != '1')
			cubed->p_x = x;
	}
	if (mlx_is_key_down(cubed->mlx, MLX_KEY_LEFT))
	{
		cubed->p_a -= turn_speed;
		if (cubed->p_a < 0)
			cubed->p_a += 2 * PI;
	}
	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_RIGHT))
	{
		cubed->p_a += turn_speed;
		if (cubed->p_a > 2 * PI)
			cubed->p_a -= 2 * PI;
	}
	cubed->p_d_x = cos(cubed->p_a) * move_speed;
	cubed->p_d_y = sin(cubed->p_a) * move_speed;
}

// void	draw_player(t_cubed *cubed)
// {
// 	if (mlx_image_to_window(cubed->mlx, cubed->p_img, cubed->p_x * TILE_MINI, cubed->p_y * TILE_MINI) == -1)
// 		terminate_free(cubed, 1, "mlx_put_image failed\n");
// }

// void	draw_player(t_cubed *cubed)
// {
// 	int	center_x = (int)(cubed->p_x * TILE_MINI);
// 	int	center_y = (int)(cubed->p_y * TILE_MINI);

// 	// Don't draw if the player is inside a wall
// 	if (cubed->map[(int)cubed->p_y][(int)cubed->p_x] == '1')
// 		return;

// 	// Draw a single red dot at the player's position
// 	mlx_put_pixel(cubed->f_img, center_x, center_y, 0xFF0000FF); // Red
// }


void draw_player(t_cubed *cubed)
{
	int center_x = TILE_MINI / 2;
	int center_y = TILE_MINI / 2;
	int	y;
	int	x;

	mlx_delete_image(cubed->mlx, cubed->p_img);
	cubed->p_img = mlx_new_image(cubed->mlx, TILE_MINI, TILE_MINI);
	y = -6;
	while (y <= 6)
	{
		x = -6;
		while (x <= 6)
		{
			mlx_put_pixel(cubed->p_img, center_x + x, center_y + y, 0xFF0000FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(cubed->mlx, cubed->p_img, cubed->p_x * TILE_MINI, cubed->p_y * TILE_MINI);
}


// static bool	draw_wf(t_cubed *cubed, char c, int x, int y)
// {
// 	mlx_image_t	*image;

// 	if (c == '0')
// 		image = cubed->f_img;
// 	else if (c == '1')
// 		image = cubed->w_img;
// 	else
// 		return (true);
// 	if (mlx_image_to_window(cubed->mlx, image, x * TILE_MINI, y * TILE_MINI) == -1)
// 		return (false);
// 	return (true);
// }

// void	movement(void *param)
// {
// 	t_cubed	*cubed;
// 	int		prev_x, prev_y;

// 	cubed = (t_cubed *)param;
// 	prev_x = (int)(cubed->p_x * TILE_MINI);
// 	prev_y = (int)(cubed->p_y * TILE_MINI);

// 	move_player(cubed);

// 	// Erase the old position by redrawing the floor *only if it's not a wall*
// 	if (cubed->map[(int)(prev_y / TILE_MINI)][(int)(prev_x / TILE_MINI)] == '0')
// 		draw_wf(cubed, '0', prev_x / TILE_MINI, prev_y / TILE_MINI);

// 	// Draw the new player dot
// 	draw_player(cubed);
// }


void	movement(void *param)
{
	t_cubed		*cubed;
	// float		prev_x;  // with current usage of mlx_put_pixel in drwaing player, this seems to be unnecessary
	// float		prev_y;
	// float		curr_x;
	// float		curr_y;

	cubed = (t_cubed *)param;
	// prev_x = cubed->p_x;
	// prev_y = cubed->p_y;

	move_player(cubed);
	// curr_x = cubed->p_x;
	// curr_y = cubed->p_y;
	// if (prev_x != curr_x || prev_y != curr_y)
	// // {
	// // 	draw_wf(cubed, '0', prev_x, prev_y); // here to simulate that affected floor tiles should be redrawn.
	// // }
	draw_player(cubed);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cubed	*cubed;

	cubed = (t_cubed *)param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		terminate_free(cubed, 0, NULL);
	/* 
		Shooting, opening doors etc might come here aswell
	*/
}

bool	init_cubed(t_cubed *cubed, char *path_to_map)
{
	ft_memset(cubed, 0, sizeof(cubed));
	cubed->map = create_map(path_to_map);
	cubed->m_height = get_height(cubed->map);
	cubed->m_width = get_width(cubed->map);
	cubed->mlx = mlx_init(cubed->m_width, cubed->m_height, "minimap", true);
	if (!cubed->mlx)
		return (false);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cubed->p_dir = get_player_dir(cubed->map);
	cubed->p_y = get_player_y(cubed->map, cubed->p_dir);
	cubed->p_x = get_player_x(cubed->map, cubed->p_y, cubed->p_dir);
	return (true);
}

int main(int ac, char **av)
{
	t_cubed	cubed;

	if (ac != 2)
		return (1);
	if (!init_cubed(&cubed, av[1]))
		return (1);
	if (!setup_images(&cubed))
		terminate_free(&cubed, 1, "Error\nProblem with setup_images.\n");
	if (!images_to_window(&cubed))
		terminate_free(&cubed, 1, "Error\nProblem with opening the window.\n");
	mlx_key_hook(cubed.mlx, &key_hook, &cubed);
	mlx_loop_hook(cubed.mlx, &movement, &cubed);
	mlx_close_hook(cubed.mlx, &close_window, &cubed);
	mlx_loop(cubed.mlx);
	terminate_free(&cubed, 0, NULL);
}
