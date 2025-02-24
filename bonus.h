#ifndef BONUS_H
# define BONUS_H

# define MINI_HEIGHT 256
# define MINI_WIDTH 180
# define TILE_MINI 8

# define GRAY 0x888888FF
# define DARK_GRAY 0x222222FF
# define RED 0xFF0000FF

typedef struct s_cubed
{
	double	p_x;
	double	p_y;
	char	p_dir;
	char	**map;
	int		m_height;
	int		m_width;
	mlx_t	*mlx;
} t_cubed;


#include "cub3d.h"

#endif