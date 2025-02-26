#include "../cub3d.h"

void	close_window(void *param)
{
	t_cubed	*cubed;

	cubed = (t_cubed *)param;
	terminate_free(cubed, 0, NULL);
	exit(0);
}

// void	key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_cubed	*cubed;


// 	cubed = (t_cubed *)param;
// 	if (keydata.key == MLX_KEY_ESCAPE)
// 		terminate_free(cubed, 0, "Game ended\n");
// 	if (mlx_is_key_down(cubed->mlx, MLX_KEY_W))
// 		cubed->p_y -= 0.1;
// 	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_S))
// 		subed->p_y += 0.1;
// 	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_LEFT))
// 		cubed->p_a -= 0.1;
// 	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_RIGHT))
// 		cubed->p_a += 0.1;
// 	if ((x != 0 || y != 0) && !move_player(cubed, x, y))
// 			return ;
// }

void move_player(t_cubed *cubed, double dx, double dy)
{
	double new_px = cubed->p_x + dx;
	double new_py = cubed->p_y + dy;
	int new_x = (int)(new_px / TILE_MINI);
	int new_y = (int)(new_py / TILE_MINI);

	// Collision check (prevent walking through walls)
	if (cubed->map[new_y][new_x] != '1')
	{
		cubed->p_x = new_px;
		cubed->p_y = new_py;
	}
}


void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cubed	*cubed;
	double	move_speed;
	double	turn_speed;

	cubed = (t_cubed *)param;
	move_speed = 4.0; // Pixels per frame
	turn_speed = 0.1; // Radians per frame

	if (keydata.key == MLX_KEY_ESCAPE)
		terminate_free(cubed, 0, "Game ended\n");

	// Handle rotation (LEFT and RIGHT keys)
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

	// Update direction vector after rotation
	cubed->p_d_x = cos(cubed->p_a) * move_speed;
	cubed->p_d_y = sin(cubed->p_a) * move_speed;

	// Handle movement (W and S keys)
	if (mlx_is_key_down(cubed->mlx, MLX_KEY_W))
		move_player(cubed, cubed->p_d_x, cubed->p_d_y);
	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_S))
		move_player(cubed, -cubed->p_d_x, -cubed->p_d_y);
}


bool	init_cubed(t_cubed *cubed, char *path_to_map)
{
	// ft_memset(cubed, 0, sizeof(cubed)); // is there need to allocate / memset cubed at this point?
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
	mlx_key_hook(cubed.mlx, key_hook, &cubed);
	mlx_close_hook(cubed.mlx, close_window, &cubed);
	mlx_loop(cubed.mlx);
	terminate_free(&cubed, 0, NULL);
}
