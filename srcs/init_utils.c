#include "../cub3d.h"

int	get_width(char **map)
{
	int	width;
	int	i;

	i = 0;
	width = (int)ft_strlen(map[i]);
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > width)
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
	int	x;

	x = 0;
	while (map[y][x] != '\0')
	{
		if (map[y][x] == p_dir)
			break ;
		x++;
	}
	return ((double)x); //+0.5 places player in the middle of the tile rather than onthe side
}

double	get_player_y(char **map, char p_dir)
{
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		if (ft_strchr(map[y], p_dir))
			break ;
		y++;
	}
	return ((double)y); //+0.5 places player in the middle of the tile rather than on the side
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