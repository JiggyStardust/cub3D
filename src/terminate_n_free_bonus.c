/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_n_free_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:23:21 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/09 11:10:51 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	free_2d_array(char **ptr)
{
	int	i;

	i = -1;
	while (ptr && ptr[++i])
		free(ptr[i]);
	free(ptr);
	ptr = NULL;
}

int	free_textures(t_data *data, int i)
{
	if (i > 0)
		mlx_delete_texture(data->textures.no);
	if (i > 1)
		mlx_delete_texture(data->textures.so);
	if (i > 2)
		mlx_delete_texture(data->textures.we);
	free(data->map_info.no);
	free(data->map_info.so);
	free(data->map_info.we);
	free(data->map_info.ea);
	return (1);
}

static void	delete_images(t_data *data)
{
	if (data->minimap)
		mlx_delete_image(data->mlx, data->minimap);
	if (data->ray)
		mlx_delete_image(data->mlx, data->ray);
	if (data->view)
		mlx_delete_image(data->mlx, data->view);
}

void	terminate_free(t_data *data, int error, char *message)
{
	if (data->map)
		free(data->map);
	mlx_delete_texture(data->textures.no);
	mlx_delete_texture(data->textures.so);
	mlx_delete_texture(data->textures.we);
	mlx_delete_texture(data->textures.ea);
	delete_images(data);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (error && message)
	{
		ft_printf("%s", message);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}
