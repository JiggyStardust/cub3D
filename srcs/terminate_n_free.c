#include "../cub3d.h"

static void	free_map(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

static void	delete_images(t_cubed *cubed)
{
	if (cubed->p_img)
		mlx_delete_image(cubed->mlx, cubed->p_img);
	if (cubed->f_img)
		mlx_delete_image(cubed->mlx, cubed->f_img);
	if (cubed->w_img)
		mlx_delete_image(cubed->mlx, cubed->w_img);
}

void	terminate_free(t_cubed *cubed, int error, char *message)
{
	if (cubed->map)
		free_map(cubed->map);
	delete_images(cubed);
	if (cubed->mlx)
		mlx_terminate(cubed->mlx);
//	free(cubed);
	if (error && message)
	{
		ft_printf("%s", message);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}
