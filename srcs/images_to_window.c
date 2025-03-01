#include "../cub3d.h"

static bool	draw_wf(t_cubed *cubed, char c, int x, int y)
{
	mlx_image_t	*image;

	if (c == '0' || c == cubed->p_dir)
		image = cubed->f_img;
	else if (c == '1')
		image = cubed->w_img;
	else
		return (true);
	if (mlx_image_to_window(cubed->mlx, image, x * TILE_MINI, y * TILE_MINI) == -1)
		return (false);
	// if (c == cubed->p_dir)
	// {
	// 	if (mlx_image_to_window(cubed->mlx, cubed->p_img, x * TILE_MINI, y * TILE_MINI) == -1)
	// 	return (false);
	// }
	return (true);
}

bool	images_to_window(t_cubed *cubed)
{
	int	x;
	int	y;

	y = 0;
	while (cubed->map[y] != NULL)
	{
		x = 0;
		while (cubed->map[y][x] != '\0')
		{
			if (!draw_wf(cubed, cubed->map[y][x], x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}