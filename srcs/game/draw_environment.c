/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:12:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/07 14:50:27 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	uint32_t	color;
	int			image_x_offset;
	int			image_y_offset;

	image_x_offset = x * sizeof(uint32_t);
	image_y_offset = y * texture->width * sizeof(uint32_t);
	color = 0;
	color += texture->pixels[image_y_offset + image_x_offset];
	color = color << 8;
	color += texture->pixels[image_y_offset + image_x_offset + 1];
	color = color << 8;
	color += texture->pixels[image_y_offset + image_x_offset + 2];
	color = color << 8;
	color += texture->pixels[image_y_offset + image_x_offset + 3];
	return (color);
}

void	draw_vertical_color(t_map *map, t_vector start, int height,
		uint32_t color)
{
	int	y;

	y = 0;
	while (y < height)
	{
		mlx_put_pixel(map->canvas, start.x, start.y + y, color);
		y++;
	}
}

void	draw_vertical_texture(t_map *map, t_vector canvas_start, int height, mlx_texture_t	*texture, t_vector image_start)
{
	int	y;
	int	image_x;
	int	image_y;

	image_x = image_start.x;
	y = 0;
	while (y < height)
	{
		double ratio = (double) y / (double) height;
		image_y = round(ratio * (double)(texture->height - 1 - (image_start.y * 2))) + image_start.y;
		mlx_put_pixel(map->canvas, canvas_start.x, canvas_start.y + y, get_texture_pixel(texture, image_x, image_y));
		y++;
	}
}

mlx_texture_t	*get_hit_texture(t_map *map, t_hitinfo hit)
{
	mlx_texture_t	*wall_texture;

	if (hit.side == NORTH)
		wall_texture = map->textures.north;
	if (hit.side == SOUTH)
		wall_texture = map->textures.south;
	if (hit.side == EAST)
		wall_texture = map->textures.east;
	if (hit.side == WEST)
		wall_texture = map->textures.west;
	return (wall_texture);
}

void	draw_environment_line(t_map *map, int x, t_hitinfo hit)
{
	t_vector		start;
	t_vector		image_start;
	mlx_texture_t	*wall_texture;
	uint32_t		scaled_wall_height;

	wall_texture = get_hit_texture(map, hit);
	scaled_wall_height = (uint32_t)(WALL_HEIGHT / hit.distance);
	start.x = x;
	start.y = 0;
	image_start.x = round(hit.side_ratio * (double) wall_texture->width);
	if (scaled_wall_height >= map->canvas->height)
	{
		// image_start.y = ((double)(scaled_wall_height - map->canvas->height) / 2) / (double) scaled_wall_height * (double) wall_texture->height;
		// image_start.y = (int) image_start.y;
		// draw_vertical_texture(map, start, map->canvas->height, wall_texture, image_start);
		uint32_t y = 0;
		while (y < map->canvas->height)
		{
			image_start.y = round(((double) y + (double)(scaled_wall_height - map->canvas->height) / 2) / (double) scaled_wall_height * (double) wall_texture->height);
			mlx_put_pixel(map->canvas, start.x, start.y + y, get_texture_pixel(wall_texture, image_start.x, image_start.y));
			y++;
		}
	}
	else
	{
		draw_vertical_color(map, start, (map->canvas->height / 2) - (scaled_wall_height / 2), map->ceiling_color);
		start.y += (map->canvas->height / 2) - (scaled_wall_height / 2);
		image_start.y = 0;
		draw_vertical_texture(map, start, scaled_wall_height, wall_texture, image_start);
		start.y += scaled_wall_height;
		draw_vertical_color(map, start, map->canvas->height - start.y, map->floor_color);
	}
}
