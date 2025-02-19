/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:25:15 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/19 16:35:22 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*void	textures()
{
}

int	check_if_valid()
{
}*/

static int	check_file_format(char *file)
{
	//if ending is not .cub, file is in wrong format
	int		i;
	char	*str;

	i = ft_strlen(file) - 4;
	if (i < 0)
		return (0);
	//file[i] == '.', file[i + 1] == 'c', file[i + 2] == 'u', file[i + 3] == 'b'
	str = file;
	*str += (ft_strlen(file) - i);
	if (ft_strncmp(str, ".cub", 5))
		return (0);
	return (1);
}

int	parsing(char **argv)
{
	//check file name is in .cub format
	if (!check_file_format(argv[1]))
		return (0);
	return (1);
}
