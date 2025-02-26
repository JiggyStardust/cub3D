#include "../cub3d.h"

void	close_window(void *param)
{
	t_cubed	*cubed;

	cubed = (t_cubed *)param;
	terminate_free(cubed, 0, NULL);
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cubed	*cubed;


	cubed = (t_cubed *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		terminate_free(cubed, 0, "Game ended\n");
	if (mlx_is_key_down(cubed->mlx, MLX_KEY_W))
		cubed->p_y -= 0.1;
	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_S))
		subed->p_y += 0.1;
	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_LEFT))
		cubed->p_a -= 0.1;
	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_RIGHT))
		cubed->p_a += 0.1;
	if ((x != 0 || y != 0) && !move_player(cubed, x, y))
			return ;
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
