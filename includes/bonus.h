#ifndef BONUS_H
# define BONUS_H

# define MINI_HEIGHT 256
# define MINI_WIDTH 180
# define TILE_MINI 50

# define GRAY 0x888888FF
# define DARK_GRAY 0x222222FF
# define RED 0xFF0000FF
# define PI 3.14159265359

# include "cub3d.h"
# include <math.h>

char	**create_map(char *path);
bool	setup_images(t_data *data);
void	terminate_free(t_data *data, int error, char *message);

char	get_player_dir(char **map);
int		get_height(char **map);
int		get_width(char **map);
float	get_player_x(char **map, int y, char p_dir);
float	get_player_y(char **map, char p_dir);
float	get_player_angle(char dir);

bool	images_to_window(t_data *data);

// bool	move_player(t_data *data, int x, int y);
void move_player(t_data *data);

#endif