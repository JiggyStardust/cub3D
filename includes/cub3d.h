/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:28:22 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/04 13:27:45 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "MLX42/include/MLX42/MLX42_Int.h"
# include "bonus.h"
# include <fcntl.h>

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

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

typedef struct s_data
{
	char	*file;
	t_map	map_info;
	enum e_type	*map;
	float	p_x; // player X position
	float	p_y; // player Y position
	float	p_d_x; // player delta X
	float	p_d_y; // player delta Y
	float	p_a; // player angle
	int 	x; // player pos in X tiles
	int		y; // player pos in Y tiles
	char	p_dir; // marks player and beginning direction
	mlx_t	*mlx;
	mlx_image_t		*mini_p_img; // player image
	mlx_image_t		*mini_f_img; // floor image
	mlx_image_t		*mini_w_img; // wall image
}	t_data;

//main.c
//parsing.c
int		parsing(t_data *data, char **argv);

//utils.c
void	free_2d_array(char **ptr);
int		to_map(t_data *data, char *line, int j);
t_position	get_pos(t_data *data, int i);
enum e_type	get_type(t_data *data, int row, int col);

#endif

