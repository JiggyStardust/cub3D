/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:27:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/08 10:42:33 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void get_pixel(mlx_texture_t *texture, uint32_t *color, int xy)
{
	t_rgb rgb;
	
	if (xy + 3 >= (texture->width * texture->height))
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
			data->texture = data->textures.EA;
		else
			data->texture = data->textures.WE;
	}
	else
	{
		if (sin(ray.angle) < 0)
			data->texture = data->textures.NO;
		else
			data->texture = data->textures.SO;
	}
}

static uint32_t get_x(t_data *data, t_ray ray)
{
	int			t_x;
	double		x;

	if (ray.side == VERTICAL)
		x = ray.y + ray.len2 * sin(ray.angle);
	else
		x = ray.x + ray.len2 * cos(ray.angle);
	x -= floor((x));
	t_x = x * (double)data->texture->width;
	if ((ray.side == VERTICAL && cos(ray.angle) > 0) || (ray.side == HORIZONTAL && sin(ray.angle) < 0))
		t_x = data->texture->width - t_x - 1;
	if (t_x < 0)
		t_x = 0;
	if (t_x >= data->texture->width)
		t_x = data->texture->width - 1;
	return ((uint32_t)t_x);
}

mlx_image_t *draw_ray(t_data *data, t_ray ray, int x, mlx_image_t *img)
{

	float	wall_height;
	int		wall_top;
	double	t_pos;
	uint32_t	text_x;
	uint32_t	text_y;
	double	step;
	uint32_t	color;

	wall_height = HEIGHT / ray.len;
	wall_top = (HEIGHT / 2) - wall_height / 2;
	if (wall_top < 0)
		wall_top = 0;
	choose_texture(data, ray);
	text_x = get_x(data, ray);
	step = (double) data->texture->height / wall_height;
	t_pos = (wall_top - HEIGHT / 2 + wall_height / 2) * step;
	while (wall_top <= (HEIGHT / 2) + wall_height / 2)
	{
		text_y = (uint32_t) t_pos;
		if (text_y < 0)
			text_y = 0;
		if (text_y >= data->texture->height)
			text_y = (uint32_t) data->texture->height - 1;
		get_pixel(data->texture, &color, (data->texture->width * text_y + text_x));
		mlx_put_pixel(img, x, wall_top, color);
		t_pos += step;
		wall_top++;
		if (wall_top == HEIGHT)
			break ;
	}
	return (img);
}
