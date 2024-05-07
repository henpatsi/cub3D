/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/07 12:31:47 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_visuals(t_map *map)
{
	map->canvas = mlx_new_image(map->mlx, map->mlx->width,
			map->mlx->height);
	mlx_image_to_window(map->mlx, map->canvas, 0, 0);
	mlx_set_instance_depth(map->canvas->instances, 0);
	return (update_visuals(map));
}

uint32_t	get_image_pixel(mlx_texture_t *texture, int x, int y)
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

t_vector	calculate_ray_dir(t_map *map, int x)
{
	t_vector	ray_dir;
	double		screen_position;

	screen_position = 2 * (double) x / (double) map->canvas->width - 1;
	ray_dir.x = map->player.dir.x + map->player.cam_plane.x * screen_position;
	ray_dir.y = map->player.dir.y + map->player.cam_plane.y * screen_position;
	return (ray_dir);
}

void	draw_vertical_line(t_map *map, t_vector start, int height,
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

void	draw_wall(t_map *map, int x, t_hitinfo hit)
{
	t_vector		start;
	mlx_texture_t	*wall_texture;
	uint32_t		scaled_wall_height;
	int				image_x;
	int				image_y;
	uint32_t		y;
	uint32_t		color;

	wall_texture = NULL;
	if (hit.side == NORTH)
		wall_texture = map->textures.north;
	if (hit.side == SOUTH)
		wall_texture = map->textures.south;
	if (hit.side == EAST)
		wall_texture = map->textures.east;
	if (hit.side == WEST)
		wall_texture = map->textures.west;
	scaled_wall_height = (uint32_t)(WALL_HEIGHT / hit.distance);
	start.x = x;
	start.y = 0;
	image_x = round(hit.side_ratio * (double) wall_texture->width);
	if (scaled_wall_height >= map->canvas->height)
	{
		y = 0;
		while (y < map->canvas->height)
		{
			image_y = round(((double) y + (double)(scaled_wall_height - map->canvas->height) / 2) / (double) scaled_wall_height * (double) wall_texture->height);
			color = get_image_pixel(wall_texture, image_x, image_y);
			mlx_put_pixel(map->canvas, start.x, start.y + y, (uint32_t) color);
			y++;
		}
	}
	else
	{
		draw_vertical_line(map, start, (map->canvas->height / 2) - (scaled_wall_height / 2), map->ceiling_color);
		start.y += (map->canvas->height / 2) - (scaled_wall_height / 2);
		y = 0;
		while (y < scaled_wall_height)
		{
			image_y = round((double) y / (double) scaled_wall_height * (double)(wall_texture->height - 1));
			color = get_image_pixel(wall_texture, image_x, image_y);
			mlx_put_pixel(map->canvas, start.x, start.y + y, (uint32_t) color);
			y++;
		}
		start.y += scaled_wall_height;
		draw_vertical_line(map, start, map->canvas->height - start.y, map->floor_color);
	}
}

int	update_visuals(t_map *map)
{
	t_vector	origin;
	t_hitinfo	hit;
	uint32_t	x;

	origin.x = map->player.x;
	origin.y = map->player.y;
	x = 0;
	while (x < map->canvas->width)
	{
		if (grid_raycast(&hit, map, origin, calculate_ray_dir(map, x)) == 1)
			draw_wall(map, x, hit);
		x++;
	}
	return (1);
}
