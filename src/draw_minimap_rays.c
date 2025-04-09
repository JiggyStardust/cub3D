/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_rays.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:52:39 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/09 10:26:37 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	draw_rays(t_data *data, float ray_angle, mlx_image_t *ray)
{
	int		i;
	float	map_x;
	float	map_y;
	int		xy;

	i = 0;
	while (i <= 66)
	{
		xy = get_index(data, (int)(data->player.x), \
				(int)(data->player.y));
		map_y = data->player.y;
		map_x = data->player.x;
		while (data->map[xy] == FLOOR)
		{
			map_x += cos(ray_angle) * 0.01;
			map_y += sin(ray_angle) * 0.01;
			xy = get_index(data, map_x, map_y);
			if (data->map[xy] != FLOOR)
				break ;
			mlx_put_pixel(data->ray, map_x * data->tile, \
				map_y * data->tile, RED);
		}
		ray_angle += (1.0 / 180 * PI);
		if (ray_angle >= 2 * PI)
			ray_angle -= 2 * PI;
		i++;
	}
}

void	draw_minimap_rays(t_data *data)
{
	float	ray_angle;

	if (data->ray)
		mlx_delete_image(data->mlx, data->ray);
	data->ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ray_angle = data->player.angle - (33.0 / 180 * PI);
	if (ray_angle >= 2 * PI)
		ray_angle -= 2 * PI;
	else if (ray_angle < 0)
		ray_angle += 2 * PI;
	draw_rays(data, ray_angle, data->ray);
	mlx_image_to_window(data->mlx, data->ray, data->player.x - 6, data->player.y - 6);
}
