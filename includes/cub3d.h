/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:28:22 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/21 15:34:45 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../library/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

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

typedef struct s_data
{
	//mlx etc
	char	*file;
	t_map	map_info;
	//map
}	t_data;

//main.c
//parsing.c
int	parsing(t_data *data, char **argv);

#endif

