#include "../cub3d.h"

static bool	draw_floor_n_exit(t_cubed *cubed)
{
	int	x;
	int	y;

	y = 0;
	while (cubed->map[y] != NULL)
	{
		x = 0;
		while (cubed->map[y][x] != '\0')
		{
			if (cubed->map[y][x] == ' ')
			{
				x++;
				continue ;
			}
			if (mlx_image_to_window(cubed->mlx, cubed->f_img,
					x * TILE_MINI, y * TILE_MINI) == -1)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	draw_wpc(t_cubed *cubed, char c, int x, int y)
{
	mlx_image_t	*image;

	if (c == '1')
		image = cubed->w_img;
	else
		return (true);
	if (mlx_image_to_window(cubed->mlx, image, x * TILE_MINI, y * TILE_MINI) == -1)
		return (false);
	return (true);
}

bool	images_to_window(t_cubed *cubed)
{
	int	x;
	int	y;

	y = 0;
	if (!draw_floor_n_exit(cubed))
		return (false);
	while (cubed->map[y] != NULL)
	{
		x = 0;
		while (cubed->map[y][x] != '\0')
		{
			if (!draw_wpc(cubed, cubed->map[y][x], x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}