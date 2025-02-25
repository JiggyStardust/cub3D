#ifndef BONUS_H
# define BONUS_H

# define MINI_HEIGHT 256
# define MINI_WIDTH 180
# define TILE_MINI 30

# define GRAY 0x888888FF
# define DARK_GRAY 0x222222FF
# define RED 0xFF0000FF

# include "cub3d.h"

typedef struct s_cubed
{
	double	p_x; // player X position in pixels
	double	p_y; // player Y position in pixels
	int 	x; // player pos in X tiles
	int		y; // player pos in Y tiles
	char	p_dir; // marks player and beginning direction
	char	**map;
	int		m_height;
	int		m_width;
	mlx_t	*mlx;
	mlx_image_t		*p_img; // player image
	mlx_image_t		*f_img; // floor image
	mlx_image_t		*w_img; // wall image
} t_cubed;


char	**create_map(char *path);
bool	setup_images(t_cubed *cubed);
void	terminate_free(t_cubed *cubed, int error, char *message);

char	get_player_dir(char **map);
int		get_height(char **map);
int		get_width(char **map);
double	get_player_x(char **map, int y, char p_dir);
double	get_player_y(char **map, char p_dir);

bool	images_to_window(t_cubed *cubed);

bool	move_player(t_cubed *cubed, int x, int y);

#endif