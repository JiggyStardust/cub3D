/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:29:39 by hpirkola          #+#    #+#             */
/*   Updated: 2025/03/14 16:17:16 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_data(t_data *data)
{
	data->map_info.height = 0;
	data->map_info.width = 0;
	data->map_info.NO = NULL;
	data->map_info.SO = NULL;
	data->map_info.WE = NULL;
	data->map_info.EA = NULL;
	data->map_info.floor_color.found = 0;
	data->map_info.ceiling_color.found = 0;
	data->map = NULL;
	data->player.found = 0;
}

void	cleanup(t_data *data)
{
	//if (data->file)
		//free(data->file);
	if (data->map)
		free(data->map);
	if (data->map_info.NO)
		free(data->map_info.NO);
	if (data->map_info.SO)
		free(data->map_info.SO);
	if (data->map_info.WE)
		free(data->map_info.WE);
	if (data->map_info.EA)
		free(data->map_info.EA);
}

// float	get_ray_length(t_ray *ray, float map_x, float map_y, int i, t_data *data)
// {
// 	float	hypotenuse;
// 	int		x;
// 	int		y;

// 	x = (int)map_x;
// 	y = (int)map_y;
// 	(void)i;
// 	// if ((float)map_x < ray->x && fmodf((float)map_x, (int)map_x) != 0)
// 	// 	map_x++;
// 	// if ((float)map_y < ray->y && fmodf((float)map_y, (int)map_y) != 0)
// 	// 	map_y++;
// 	ray->dx = fabsf(map_x - ray->x);
// 	printf("i: %d\ndx: %f\n", i, ray->dx);
// 	ray->dy = fabsf(map_y - ray->y);
// 	printf("dy: %f\n", ray->dy);
// 	hypotenuse = sqrt(pow(ray->dx, 2) + pow(ray->dy, 2)); // * cos(PI / 2 - ray.angle); it wasn't supposed to be rayangle, i feel silly
// 	// printf("\n\nhyp1: %f\n", hypotenuse);
// 	hypotenuse = hypotenuse * cos(data->player.angle - ray->angle);
// 	// printf("hyp2: %f\n", hypotenuse);
// 	// printf("the i: %d, abs division: %f\nthe multiplier: %f\n", i, deg, cos(deg));
// 	return (hypotenuse);
// }

mlx_image_t *draw_ray(t_data *data, t_ray ray, int x, mlx_image_t *img)
{

	float	center;
	float	wall_height;
	int		y;
	(void)data;

	center = HEIGHT / 2;
	wall_height = HEIGHT / ray.len;
	printf("raylen = %f\n", ray.len);
	y = center - wall_height / 2;
	while (y <= center + wall_height / 2)
	{
		mlx_put_pixel(img, x, y, RED);
		y++;
	}
	return (img);
}

float	cast_ray(t_data *data, t_ray *ray)
{
	int		map_x;
	int		map_y;
	float	delta_x;
	float	delta_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;

	map_x = (int)ray->x;
	map_y = (int)ray->y;

	if (cos(ray->angle) != 0)
		delta_x = fabs(1 / cos(ray->angle));
	if (sin(ray->angle) != 0)
		delta_y = fabs(1 / sin(ray->angle));
	if (cos(ray->angle) > 0)
		step_x = 1;
	else
		step_x = -1;

	if (sin(ray->angle) > 0)
		step_y = 1;
	else
		step_y = -1;
		
	// Calculate initial side distances
	if (step_x > 0)
		side_dist_x = (map_x + 1.0 - ray->x) * delta_x;
	else
		side_dist_x = (ray->x - map_x) * delta_x;

	if (step_y > 0)
		side_dist_y = (map_y + 1.0 - ray->y) * delta_y;
	else
		side_dist_y = (ray->y - map_y) * delta_y;
	
	// DDA loop
	while (data->map[map_y * data->map_info.width + map_x] == FLOOR)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
		}
		else if (side_dist_x > side_dist_y)
		{
			side_dist_y += delta_y;
			map_y += step_y;
		}
	}
	// Assign the correct ray length
	if (side_dist_x < side_dist_y)
		return (fabs(side_dist_x));
	else
		return (fabs(side_dist_y));
}


mlx_image_t	*raycaster(t_data *data)
{
	t_ray 		ray;
	int			i;
	mlx_image_t *img;

	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ray.x = data->player.x;
	ray.y = data->player.y;
	ray.angle = data->player.angle - (33.0 / 180 * PI);

	// Ensure angle is within 0 to 2*PI range
	if (ray.angle > 2 * PI)
		ray.angle -= 2 * PI;
	else if (ray.angle < 0)
		ray.angle += 2 * PI;

	i = 0;
	while (i < WIDTH)
	{
		// Cast a ray and determine its length
		ray.len = cast_ray(data, &ray);
		printf("ray len: %f\n", ray.len);
		ray.len *= cos(data->player.angle - ray.angle);
		// Draw the wall slice based on ray length
		draw_ray(data, ray, i, img);

		// Move to the next ray angle
		ray.angle += ((66.0 / 180 * PI) / WIDTH);
		if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		i++;
	}
	return (img);
}


// mlx_image_t	*raycaster(t_data *data)
// {
// 	t_ray 		ray;
// 	int			xy;
// 	float		map_x;
// 	float		map_y;
// 	int			i;
// 	mlx_image_t *img;

// 	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
// 	ray.x = data->player.x;
// 	ray.y = data->player.y;
// 	ray.angle = data->player.angle - (33.0 / 180 * PI);
// 	if (ray.angle > 2 * PI)
// 		ray.angle -= 2 * PI;
// 	else if (ray.angle < 0)
// 		ray.angle += 2 * PI;
// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		map_x = ray.x;
// 		map_y = ray.y;
// 		xy = get_index_of_rov_and_col(data, (int)(data->player.x), (int)(data->player.y), 1);
// 		while (data->data->map[xy] == FLOOR)
// 		{
// 			xy = get_index_of_rov_and_col(data, (int)(map_x - cos(ray.angle) * 0.01), (int)(map_y - sin(ray.angle) * 0.01), 1);
// 			if (data->data->map[xy] == FLOOR)
// 			{
// 				map_y -= sin(ray.angle) * 0.01;
// 				map_x -= cos(ray.angle) * 0.01;
// 			}
// 		}
// 		ray.len = get_ray_length(&ray, map_x, map_y, i, data);
// 		draw_ray(data, ray, i, img);
// 		ray.angle += ((66.0 / 180 * PI) / WIDTH);
// 		if (ray.angle > 2 * PI)
// 			ray.angle -= 2 * PI;
// 		// printf("ray.angle: %f, player.angle: %f\n\n", ray.angle, data->player.angle);
// 		i++;
// 	}
// 	return (img);
// }


int	main(int argc, char **argv)
{
	t_data	data;
	mlx_image_t *rimg;

	//check if map is valid and parse
	if (argc != 2)
		return (ft_putstr_fd("Example: ./cub3D file.cub\n", 2), 1);
	init_data(&data);
	if (!parsing(&data, argv))
		return (cleanup(&data), 1);
	data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!data.mlx)
		return (false);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	data.player.angle = get_player_angle(data.player.p_dir);
	data.player.d_x = cos(data.player.angle) * MOVE_SPEED;
	data.player.d_y = sin(data.player.angle) * MOVE_SPEED;
	if (!setup_images(&data))
		terminate_free(&data, 1, "Error\nProblem with setup_images.\n");
	rimg = raycaster(&data);
	if (!images_to_window(&data, rimg))
		terminate_free(&data, 1, "Error\nProblem with opening the window.\n");
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &movement, &data);
	mlx_close_hook(data.mlx, &close_window, &data);
	mlx_loop(data.mlx);
	cleanup(&data);
	terminate_free(&data, 0, NULL);
	return (0);
}
