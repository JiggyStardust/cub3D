#include "cub3d.h"

char temp_map[MINI_HEIGHT][MINI_WIDTH] = 
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', 'N', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

int	get_width(char **map)
{
	int	width;
	int	i;

	i = 0;
	width = (int)ft_strlen(map[i]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	width *= TILE_MINI;
	return (width);
}

int	get_height(char **map)
{
	int	i;
	int	height;

	i = 0;
	while (map[i] != NULL)
		i++;
	height = i * TILE_MINI;
	return (height);
}

double	get_player_x(char **map, int y, char p_dir)
{
	double	x;

	x = 0;
	while (map[y][x] != '\0')
	{
		if (map[y][x] == cubed->p_dir)
			break ;
		x++;
	}
	return (x + 0.5); //+0.5 places player in the middle of the tile rather than onthe side
}

double	get_player_y(char **map, char p_dir)
{
	double	y;

	y = 0;
	while (map[y] != NULL)
	{
		if (ft_strchr(map[y], cubed->p_dir))
			break ;
		y++;
	}
	return (y + 0.5); //+0.5 places player in the middle of the tile rather than on the side
}

char	get_player_dir(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		if (ft_strchr(map[i], 'N'))
			return ('N');
		else if (ft_strchr(map[i], 'S'))
			return ('S');
		else if (ft_strchr(map[i], 'W'))
			return ('W');
		else if (ft_strchr(map[i], 'E'))
			return ('E');
		i++;
	}
	return ('\0');
}

bool	init_cubed(t_cubed *cubed, char *path_to_map)
{
	ft_memset(cubed, 0, sizeof(cubed));
	cubed->map = map;
	cubed->m_height = get_height(cubed->map);
	cubed->m_width = get_width(cubed->map);
	cubed->mlx = mlx_init(cubed->m_width, cubed->m_height, "minimap", true);
	if (!solong->mlx)
		return (false);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cubed->p_dir = get_player_dir(cubed->map);
	cubed->p_y = get_player_y(cubed->map, cubed->p_dir);
	cubed->p_x = get_player_x(cubed->map, cubed->p_y, cubed->p_dir);
}

int main(int ac, char **av)
{
	t_cubed	cubed;

	if (!init_cubed(&cubed), av[1])
		return (1);
	if (!setup_images(&cubed))
		terminate_free(&cubed, 1, "Error\nProblem with setup_images.\n");
	if (!images_to_window(&cubed))
		terminate_free(&cubed, 1, "Error\nProblem with opening the window.\n");
	
}
