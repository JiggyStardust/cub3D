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
