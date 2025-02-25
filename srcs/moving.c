#include "cub3d.h"

static bool	valid_move(t_cubed *cubed, int x, int y)
{
	if (cubed->map[y][x] == '1')
		return (false);
	else
		return (true);
}

static bool	handle_move_logic(t_cubed *cubed, int x_new, int y_new)
{
	if (!valid_move(cubed, x_new, y_new))
		return (false);
	return (true);
}

bool	move_player(t_cubed *cubed, int x, int y)
{
	int			x_new;
	int			y_new;
	mlx_image_t	*img;

	x_new = cubed->p_x + x;
	y_new = cubed->p_y + y;
	if (!handle_move_logic(cubed, x_new, y_new))
		return (false);
	else
		img = cubed->f_img;
	if (mlx_image_to_window(cubed->mlx, img,
			cubed->p_x * TILE_MINI, cubed->p_y * TILE_MINI) == -1)
		terminate_free(cubed, 1, "Error\nCouldn't render image.\n");
	cubed->map[y_new][x_new] = 'P';
	if (mlx_image_to_window(cubed->mlx, cubed->p_img,
			x_new * TILE_MINI, y_new * TILE_MINI) == -1)
		terminate_free(cubed, 1, "Error\nCouldn't render image.\n");
	cubed->p_x = x_new;
	cubed->p_y = y_new;
	return (true);
}
