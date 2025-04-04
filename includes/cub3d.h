/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:28:22 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/04 12:01:32 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_MINI 50
# define HEIGHT 1518
# define WIDTH 1518
# define RED 0xFF0000FF
# define DARK_RED 0x8B0000FF
# define PI 3.14159265359
# define MOVE_SPEED 0.1
# define TURN_SPEED 0.05
# define VERTICAL 0
# define HORIZONTAL 1

# include "../libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "MLX42/include/MLX42/MLX42_Int.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_rgb
{
	int	found;
	int	r;
	int	g;
	int	b;
	int a;
}	t_rgb;

typedef struct	s_ray
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	len;
	float	angle;
	int		side;
}	t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	float	d_x; // player delta X
	float	d_y; // player delta Y
	float	angle; // player angle
	char	p_dir;
	int	found;
}	t_player;

typedef struct s_position
{
	int	row;
	int	col;
}	t_position;

typedef struct s_map
{
	int	height;
	int	width;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_map;

enum	e_type
{
	FLOOR,
	WALL,
	PADDING,
	N,
	S,
	W,
	E
};

enum	dir_type
{
	FORWARD,
	REVERSE,
	LEFT,
	RIGHT
};

typedef struct s_data
{
	char	*file;
	t_map	map_info;
	enum e_type	*map;
	double	text_x;
	double	text_y;
	mlx_texture_t *texture;
	t_player	player;
	mlx_t	*mlx;
	mlx_image_t		*mini_p_img; // player image
	mlx_image_t		*mini_f_img; // floor image
	mlx_image_t		*mini_w_img; // wall image
	mlx_image_t		*floor_img;
	mlx_image_t		*ceiling_img;
	mlx_image_t		*ray;
	mlx_image_t		*view;
}	t_data;

//main.c
//parsing.c
int		parsing(t_data *data, char **argv);

//utils.c
void	free_2d_array(char **ptr);
int		to_map(t_data *data, char *line, int j);
t_position	get_pos(t_data *data, int i);
enum e_type	get_type(t_data *data, int row, int col);
t_player    player(char c, int j, t_data *data);

//validate.c
int	is_valid(t_data *data);
//init_utils_bonus.c 
/*******************************************************************************
 * @param i the index on the map
 * @param size map arrays size (height*width)
 * @param pos a struct which portrays index position in columns and rows.
 * 
 * We search for player enum (S, W, N or E) on the map array, then get position by 
 * calling get_pos(data, i). We then update player.y (pos.row) and player.x 
 * (pos.col) into t_data struct.
 ******************************************************************************/
void	get_player_x_y(enum e_type *map, t_data *data);
/*******************************************************************************
 *  Updates @param angle of t_player, which is the direction the player is faced
 * in the beginning. Angle is handled in radians.
 ******************************************************************************/
float	get_player_angle(char dir);

// image_handling_bonus.c
/*******************************************************************************
 * Set's up minimap's images by converting minimap textures into mlx_image_t images,
 * resizing them if necessary and finally saves them into t_data struct.
 ******************************************************************************/
bool	setup_images(t_data *data);

// terminate_n_free.c
/*******************************************************************************
 * @param error if set to 0, the program was succesful / no error encountered.
 * @param message optional message for signaling specific error for example.
 * 
 * Frees allocated memory, deletes pictures, prints a message (optional) and exits
 * with the exit status defined by the caller.
 ******************************************************************************/
void	terminate_free(t_data *data, int error, char *message);

// hooks_bonus.c
/*******************************************************************************
 *  Hook for closing the window. The function calls terminate_free() which frees
 * 	allocated memory, deletes pictures and exits.
 ******************************************************************************/
void	close_window(void *param);
/*******************************************************************************
 * If ESC is pressed, we close the window by calling terminate_free() which frees
 * 	allocated memory, deletes pictures and exits.
 * 
 * Later the action for shooting, opening doors etc bonus stuff might be handled
 * here aswell.
 ******************************************************************************/
void	key_hook(mlx_key_data_t keydata, void *param);

// images_to_window_bonus.c
/*******************************************************************************
 *  First draws minimaps floor and wall tiles index (x and y) at a time by calling a
 * static function draw_floor_n_walls(). 
 * Lastly draws the player image @param mini_p_img on top.
 ******************************************************************************/
// bool	images_to_window(t_data *data);
bool	images_to_window(t_data *data);

// moving_bonus.c

/*******************************************************************************
 * We first update the players movements by calling move_up_down(data) and 
 * move_left_right. Then we move the player image by calling move_player_image().
 ******************************************************************************/
void	movement(void *param);

/*******************************************************************************
 * @param move_speed how many pixels we move (forward or backwards).
 * @param move_speed how many pixels we turn.
 * @param x players X position after potential move (if not hitting a wall)
 * @param y players Y position after potential move (if not hitting a wall)
 * @param i index on the map (1D enum array), helps us define movement limitations
 * (WALLS).
 * 
 * The function updates t_player's x, y, angle, delta_x and delta_y based on which keys are pressed.
 * A = left, D = right, < rotate left, > rotate right.
 ******************************************************************************/
void	move_left_right(t_data *data);

/*******************************************************************************
 * @param move_speed how many pixels we move (forward or backwards).
 * @param move_speed how many pixels we turn.
 * @param x players X position after potential move (if not hitting a wall)
 * @param y players Y position after potential move (if not hitting a wall)
 * @param i index on the map (1D enum array), helps us define movement limitations
 * (WALLS).
 * 
 * The function updates t_player's x, y, angle, delta_x and delta_y based on which keys are pressed.
 * W = forward, S = backwards, < rotate left, > rotate right.
 ******************************************************************************/
void	move_up_down(t_data *data);
/*******************************************************************************
 * We move the player picture using mlx_image_t's instances, which are created
 * when player image is drawn on top of the map with mlx_image_to_window()
 ******************************************************************************/
void	move_player_image(t_data *data);


mlx_image_t *draw_ray(t_data *data, t_ray ray, int i, mlx_image_t *img);
int		get_index_of_rov_and_col(t_data *data, int x, int y, enum dir_type gear);
mlx_image_t	*raycaster(t_data *data);
#endif
