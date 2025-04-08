/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:30:25 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/08 12:03:22 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"


void	dda(t_data *data, t_ray *ray, int step_x, int step_y)
{
	int		map_x;
	int		map_y;
	int		xy;

	map_x = (int)ray->x;
	map_y = (int)ray->y;
	xy = get_index_of_rov_and_col(data, map_x, map_y);
	while (data->map[xy] == FLOOR)
	{
		if (ray->dist_x < ray->dist_y)
		{
			map_x += step_x;
			ray->dist_x += ray->dx;
			ray->side = VERTICAL;
		}
		else
		{
			map_y += step_y;
			ray->dist_y += ray->dy;
			ray->side = HORIZONTAL;
		}
		xy = get_index_of_rov_and_col(data, map_x, map_y);
	}
	ray->end_y = map_y;
}

static void	calc_step_x(t_data *data, t_ray *ray, int *step_x)
{
	if (cos(ray->angle) != 0)
		ray->dx = fabs(1 / cos(ray->angle));
	if (cos(ray->angle) > 0)
	{
		*step_x = 1;
		ray->dist_x = ((int)ray->x + 1.0 - ray->x) * ray->dx;
	}
	else if (cos(ray->angle) < 0)
	{
		*step_x = -1;
		ray->dist_x = (ray->x - (int)ray->x) * ray->dx;
	}
	else
	{
		*step_x = INFINITY; // is this the right approach?
		ray->dist_x = INFINITY; // is this the right approach?
		ray->dx = INFINITY; // is this the right approach?
	}
}

static void	calc_step_y(t_data *data, t_ray *ray, int *step_y)
{
	if (sin(ray->angle) != 0)
		ray->dy = fabs(1 / sin(ray->angle));
	if (sin(ray->angle) > 0)
	{
		*step_y = 1;
		ray->dist_y = ((int)ray->y + 1.0 - ray->y) * ray->dy;
	}
	else if ((sin(ray->angle) < 0))
	{
		*step_y = -1;
		ray->dist_y = (ray->y - (int)ray->y) * ray->dy;
	}
	else
	{
		*step_y = INFINITY; // is this the right approach?
		ray->dist_y = INFINITY; // is this the right approach?
		ray->dy = INFINITY; // is this the right approach?
	}
}

float	cast_ray(t_data *data, t_ray *ray)
{
	int		step_x;
	int		step_y;

	calc_step_x(data, ray, &step_x);
	calc_step_y(data, ray, &step_y);
	dda(data, ray, step_x, step_y);
	if (ray->side == VERTICAL)
		ray->dist_x -= ray->dx;
	else if (ray->side == HORIZONTAL)
		ray->dist_y -= ray->dy;
	if (fabs(ray->dist_x) < fabs(ray->dist_y))
		return (fabs(ray->dist_x));
	else
		return (fabs(ray->dist_y));
}

mlx_image_t	*raycaster(t_data *data)
{
	t_ray 		ray;
	int			i;

	if (data->view != NULL)
		mlx_delete_image(data->mlx, data->view);
	data->view = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ray.x = data->player.x;
	ray.y = data->player.y;
	ray.angle = data->player.angle - (33.0 / 180 * PI);
	if (ray.angle > 2 * PI)
		ray.angle -= 2 * PI;
	else if (ray.angle < 0)
		ray.angle += 2 * PI;
	i = -1;
	while (++i < WIDTH)
	{
		ray.len2 = cast_ray(data, &ray);
		ray.len = ray.len2 * cos(data->player.angle - ray.angle);
		draw_ray(data, ray, i, data->view);
		ray.angle += ((66.0 / 180 * PI) / WIDTH);
		if (ray.angle >= 2 * PI)
			ray.angle -= 2 * PI;
	}
	return (data->view);
}
