#include "../includes/cub3d.h"

static bool	draw_wf(t_data *data, char c, int x, int y)
{
	mlx_image_t	*image;

	if (c == '0' || c == data->p_dir)
		image = data->f_img;
	else if (c == '1')
		image = data->w_img;
	else
		return (true);
	if (mlx_image_to_window(data->mlx, image, x * TILE_MINI, y * TILE_MINI) == -1)
		return (false);
	return (true);
}

bool	images_to_window(t_data *data)
{
	int			i;
	t_position	pos;

	i = 0;
	while (i < data->map_info->width * data->map_info->height)
	{
		pos = get_pos(data->map[i]);
		if (!draw_wf(data, data->map[pos.row][[pos.col]], pos.col, pos.row))
			return (false);
		i++;
	}
	// wtf miten taa on aiemmin toiminuu??? : D 
	if (mlx_image_to_window(data->mlx, data->p_img, x * TILE_MINI, y * TILE_MINI) == -1)
		return (false);
	return (true);
}

/*	MITEN KAYTTAA GET_POS T HELMI
int i;
struct pos;

i = 0;
while (i < width * height)
{
	pos = get_pos(map[i]);
	pos.row = y;
	pos.col = x;
	i++;
}
*/