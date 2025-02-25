#include "../cub3d.h"

static mlx_image_t	*png_to_resized_img(t_cubed *cubed, const char *path_text)
{
	mlx_texture_t	*text;
	mlx_image_t		*img;

	text = mlx_load_png(path_text);
	if (!text)
		return (NULL);
	img = mlx_texture_to_image(cubed->mlx, text);
	if (!img)
	{
		mlx_delete_texture(text);
		return (NULL);
	}
	mlx_delete_texture(text);
	if (img->width != TILE_MINI || img->height != TILE_MINI)
	{
		if (!mlx_resize_image(img, TILE_MINI, TILE_MINI))
		{
			mlx_delete_image(cubed->mlx, img);
			return (NULL);
		}
	}	
	return (img);
}

bool	setup_images(t_cubed *cubed)
{
	cubed->p_img = png_to_resized_img(cubed, "./textures/player.png");
	if (!cubed->p_img)
		return (false);
	cubed->f_img = png_to_resized_img(cubed, "./textures/floor.png");
	if (!cubed->f_img)
		return (false);
	cubed->w_img = png_to_resized_img(cubed, "./textures/wall.png");
	if (!cubed->w_img)
		return (false);
	return (true);
}