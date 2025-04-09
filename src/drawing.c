/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:27:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/08 16:08:41 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	get_pixel(mlx_texture_t *texture, uint32_t *color, int xy)
{
	t_rgb	rgb;

	if ((unsigned int) xy + 3 >= (texture->width * texture->height))
		return ;
	rgb.r = texture->pixels[xy * 4];
	rgb.g = texture->pixels[xy * 4 + 1];
	rgb.b = texture->pixels[xy * 4 + 2];
	rgb.a = texture->pixels[xy * 4 + 3];
	*color = (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

static void	choose_texture(t_data *data, t_ray ray)
{
	if (ray.side == VERTICAL)
	{
		if (cos(ray.angle) > 0)
			data->texture = data->textures.ea;
		else
			data->texture = data->textures.we;
	}
	else
	{
		if (sin(ray.angle) < 0)
			data->texture = data->textures.no;
		else
			data->texture = data->textures.so;
	}
}

static uint32_t	get_x(t_data *data, t_ray ray)
{
	int			t_x;
	double		x;

	if (ray.side == VERTICAL)
		x = ray.y + ray.len2 * sin(ray.angle);
	else
		x = ray.x + ray.len2 * cos(ray.angle);
	x -= floor((x));
	t_x = x * (double)data->texture->width;
	if ((ray.side == VERTICAL && cos(ray.angle) > 0)
		|| (ray.side == HORIZONTAL && sin(ray.angle) < 0))
		t_x = data->texture->width - t_x - 1;
	if (t_x < 0)
		t_x = 0;
	if ((uint32_t) t_x >= data->texture->width)
		t_x = data->texture->width - 1;
	return ((uint32_t)t_x);
}

void	init_wall(t_wall *wall, t_ray ray)
{
	wall->height = HEIGHT / ray.len;
	wall->top = (HEIGHT / 2) - wall->height / 2;
	if (wall->top < 0)
		wall->top = 0;
	wall->bottom = wall->top + wall->height;
	if (wall->bottom >= HEIGHT)
		wall->bottom = HEIGHT - 1;
}

mlx_image_t	*draw_ray(t_data *data, t_ray ray, int x, mlx_image_t *img)
{
	t_wall		wall;
	double		t_pos;
	t_x_y		xy;
	double		step;
	uint32_t	color;

	init_wall(&wall, ray);
	choose_texture(data, ray);
	xy.x = get_x(data, ray);
	step = (double) data->texture->height / wall.height;
	t_pos = (wall.top - HEIGHT / 2 + wall.height / 2) * step;
	while (wall.top <= wall.bottom)
	{
		xy.y = (uint32_t) t_pos;
		if (xy.y < 0)
			xy.y = 0;
		if (xy.y >= data->texture->height)
			xy.y = (uint32_t) data->texture->height - 1;
		get_pixel(data->texture, &color, (data->texture->width * xy.y + xy.x));
		mlx_put_pixel(img, x, wall.top, color);
		t_pos += step;
		wall.top++;
	}
	return (img);
}
