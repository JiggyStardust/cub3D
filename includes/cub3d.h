/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:28:22 by hpirkola          #+#    #+#             */
/*   Updated: 2025/04/09 12:18:39 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

typedef struct s_rgb
{
	int	found;
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgb;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_textures;

typedef struct wall
{
	float	height;
	int		top;
	int		bottom;
}	t_wall;

typedef struct s_ray
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	dist_x;
	float	dist_y;
	double	end_x;
	double	end_y;
	float	len;
	float	len2;
	float	angle;
	int		side;
}	t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	float	d_x;
	float	d_y;
	float	d_lr_x;
	float	d_lr_y;
	float	new_x;
	float	new_y;
	float	angle;
	char	p_dir;
	int		found;
}	t_player;

typedef struct s_position
{
	int	row;
	int	col;
}	t_position;

typedef struct s_map
{
	int		height;
	int		width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
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

typedef struct s_x_y
{
	uint32_t	x;
	uint32_t	y;
}	t_x_y;

typedef struct s_data
{
	char			*file;
	int				tile;
	enum e_type		*map;
	t_map			map_info;
	t_player		player;
	t_textures		textures;
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*minimap;
	mlx_image_t		*floor_img;
	mlx_image_t		*ceiling_img;
	mlx_image_t		*ray;
	mlx_image_t		*view;
}	t_data;

//parsing.c
int			parsing(t_data *data, char **argv);
int			check_file_format(char *file, char *format);
int			all_found(t_data *data);

//map.c
int			get_map_size(t_data *data);
int			get_map(t_data *data);
//int			to_map(t_data *data, char *line, int j);

//utils.c
void		free_2d_array(char **ptr);
t_position	get_pos(t_data *data, int i);
int			add_texture(char *src, char **dest);
int			set_color(char **rgb, t_rgb *colors);
int			is_texture_or_color(char *line);
void		read_to_end(int fd);
int			get_index(t_data *data, int x, int y);

//textures_and_colors.c
int			get_texture_and_color(t_data *data);
int			load_textures(t_data *data);

//validate.c
int			is_valid(t_data *data);

//terminate_n_free_bonus.c
int			free_textures(t_data *data, int i);

//draw_minimap_rays.c

/*******************************************************************************
 * This function is called after the POV is already drawn. Here we have a sepa-
 * rate and a rougher version of "raycasting" and detecting wall hits (not using)
 * DDA.
 *****************************************************************************/
void		draw_minimap_rays(t_data *data);

//drawing.c

/*******************************************************************************
 *  Draws the walls using textures, mlx_put_pixel() and the ray length we've 
 * gotten from cast_ray.
 *****************************************************************************/
mlx_image_t	*draw_ray(t_data *data, t_ray ray, int x, mlx_image_t *img);

// hooks_bonus.c

/*******************************************************************************
 *  Hook for closing the window. The function calls terminate_free() which frees
 * 	allocated memory, deletes pictures and exits.
 *****************************************************************************/
void		close_window(void *param);

/*******************************************************************************
 * If ESC is pressed, we close the window by calling terminate_free() which frees
 * 	allocated memory, deletes pictures and exits.
 * 
 * Later the action for shooting, opening doors etc bonus stuff might be handled
 * here aswell.
 *****************************************************************************/
void		key_hook(mlx_key_data_t keydata, void *param);

// image_handling_bonus.c

/*******************************************************************************
 * Set's up minimap's images by converting minimap textures into mlx_image_t 
 * images, resizing them if necessary and finally saves them into t_data struct.
 *****************************************************************************/
bool		setup_images(t_data *data);

//raycasting.c

/*******************************************************************************
 *  Calculates the length until a wall is hit using DDA (digital differential 
 * analysis) algorithm.
 *****************************************************************************/
float		cast_ray(t_data *data, t_ray *ray);

/*******************************************************************************
 * Creates the game image using mlx_new_image(), creates a @param ray and 
 * proceeds to calculate the length of every individual ray at a time and drawd
 * the textures based on the rays length.
 *****************************************************************************/
mlx_image_t	*raycaster(t_data *data);

//init_utils.c

/*******************************************************************************
 * @param player player struct that's created
 * @param pos a struct which portrays index position in columns and rows.
 * 
 * Creates struct for player, and sets it spawning position on the map
 * by calling get_pos(data, i). We then update player.y (pos.row) and player.x 
 * (pos.col) based on results.
 *****************************************************************************/
t_player	player(char c, int j, t_data *data);

/*******************************************************************************
 *  Updates @param angle of t_player, which is the direction the player is faced
 * in the beginning. Angle is handled in radians.
 *****************************************************************************/
float		get_player_angle(char dir);

// terminate_n_free.c
/*******************************************************************************
 * @param error if set to 0, the program was succesful / no error encountered.
 * @param message optional message for signaling specific error for example.
 * * Frees allocated memory, deletes pictures, prints a message (optional) and
 * exits with the exit status defined by the caller.
 *****************************************************************************/
void		terminate_free(t_data *data, int error, char *message);

// images_to_window_bonus.c
/*******************************************************************************
 * First draws minimaps floor and wall tiles index (x and y) at a time by 
 * calling a static function draw_floor_n_walls(). 
 * Lastly draws the player image @param mini_p_img on top.
 *****************************************************************************/
// bool	images_to_window(t_data *data);
bool		images_to_window(t_data *data);

// moving_bonus.c

/*******************************************************************************
 * We first update the players movements by calling move_up_down(data) and 
 * move_left_right. Then we move the player image by calling 
 * move_player_image().
 *****************************************************************************/
void		movement(void *param);

/*******************************************************************************
 * @param move_speed how many pixels we move (forward or backwards).
 * @param move_speed how many pixels we turn.
 * @param x players X position after potential move (if not hitting a wall)
 * @param y players Y position after potential move (if not hitting a wall)
 * @param i index on the map (1D enum array), helps us define movement limits
 * (WALLS).
 * 
 * The function updates t_player's x, y, angle, delta_x and delta_y based on 
 * which keys are pressed. A = left, D = right, < rotate left, > rotate right.
 *****************************************************************************/
void		move_left_right(t_data *data);

/*******************************************************************************
 * @param move_speed how many pixels we move (forward or backwards).
 * @param move_speed how many pixels we turn.
 * @param x players X position after potential move (if not hitting a wall)
 * @param y players Y position after potential move (if not hitting a wall)
 * @param i index on the map (1D enum array), helps us define movement limits
 * (WALLS).
 * 
 * The function updates t_player's x, y, angle, delta_x and delta_y based on 
 * which keys are pressed. W = forward, S = backwards, < rotate left, > rotate 
 * right.
 *****************************************************************************/
void		move_up_down(t_data *data);

#endif
