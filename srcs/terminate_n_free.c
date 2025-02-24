#include "../cub3d.h"

void	terminate_free(t_cubed *cubed, int error, char *message)
{
	int	moves;

	moves = cubed->moves;
	if (cubed->map)
		free_map(cubed->map);
	delete_images(cubed);
	if (cubed->mlx)
		mlx_terminate(cubed->mlx);
	if (error && message)
	{
		ft_printf("%s", message);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}
