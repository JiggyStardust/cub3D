/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_n_free_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:23:21 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/08 13:03:53 by sniemela         ###   ########.fr       */
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
}

static void	delete_images(t_data *data)
{
	// if (data->mini_p_img)
	// 	mlx_delete_image(data->mlx, data->mini_p_img);
	// if (data->mini_f_img)
	// 	mlx_delete_image(data->mlx, data->mini_f_img);
	// if (data->mini_w_img)
	// 	mlx_delete_image(data->mlx, data->mini_w_img);
	if (data->minimap)
		mlx_delete_image(data->mlx, data->minimap);
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
