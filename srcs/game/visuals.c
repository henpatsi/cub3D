/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/30 10:10:29 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_visuals(t_map *map)
{
	map->images.draw = mlx_new_image(map->mlx, map->mlx->width,
			map->mlx->height);
	mlx_image_to_window(map->mlx, map->images.draw, 0, 0);
	mlx_set_instance_depth(map->images.draw->instances, 0);
	return (update_visuals(map));
}

uint32_t	abgr_to_rgba(uint32_t abgr)
{
	uint32_t	rgba;
	uint8_t		byte[4];

	byte[0] = (abgr >> 24) & 0xFF;
	byte[1] = (abgr >> 16) & 0xFF;
	byte[2] = (abgr >> 8) & 0xFF;
	byte[3] = (abgr) & 0xFF;
	rgba = byte[3];
	rgba = rgba << 8;
	rgba += byte[2];
	rgba = rgba << 8;
	rgba += byte[1];
	rgba = rgba << 8;
	rgba += byte[0];
	return (rgba);
}

uint32_t	get_image_pixel(mlx_image_t *image, int x, int y)
{
	uint32_t	color;
	int			image_x_offset;
	int			image_y_offset;

	image_x_offset = x * 4;
	image_y_offset = y * image->width * 4;
	ft_memcpy(&color, &image->pixels[image_y_offset + image_x_offset], 4);
	color = abgr_to_rgba(color);
	return (color);
}

t_vector	calculate_ray_dir(t_map *map, int x)
{
	t_vector	ray_dir;
	double		screen_position;

	screen_position = 2 * (double) x / (double) map->images.draw->width - 1;
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
		mlx_put_pixel(map->images.draw, start.x, start.y + y, color);
		y++;
	}
}

void	draw_wall(t_map *map, int x, t_hitinfo hit)
{
	t_vector	start;
	mlx_image_t	*wall_image;
	uint32_t	scaled_wall_height;
	int			image_x;
	int			image_y;
	uint32_t	y;
	uint32_t	color;

	if (hit.side == NORTH)
		wall_image = map->images.north;
	if (hit.side == SOUTH)
		wall_image = map->images.south;
	if (hit.side == EAST)
		wall_image = map->images.east;
	if (hit.side == WEST)
		wall_image = map->images.west;
	scaled_wall_height = (uint32_t)(WALL_HEIGHT / hit.distance);
	start.x = x;
	start.y = 0;
	image_x = round(hit.side_ratio * (double) wall_image->width);
	if (scaled_wall_height >= map->images.draw->height)
	{
		y = 0;
		while (y < map->images.draw->height)
		{
			image_y = round(((double) y + (double)(scaled_wall_height - map->images.draw->height) / 2) / (double) scaled_wall_height * (double) wall_image->height);
			color = get_image_pixel(wall_image, image_x, image_y);
			mlx_put_pixel(map->images.draw, start.x, start.y + y, (uint32_t) color);
			y++;
		}
	}
	else
	{
		draw_vertical_line(map, start, (map->images.draw->height / 2) - (scaled_wall_height / 2), map->ceiling_color);
		start.y += (map->images.draw->height / 2) - (scaled_wall_height / 2);
		y = 0;
		while (y < scaled_wall_height)
		{
			image_y = round((double) y / (double) scaled_wall_height * (double) wall_image->height);
			color = get_image_pixel(wall_image, image_x, image_y);
			mlx_put_pixel(map->images.draw, start.x, start.y + y, (uint32_t) color);
			y++;
		}
		start.y += scaled_wall_height;
		draw_vertical_line(map, start, map->images.draw->height - start.y, map->floor_color);
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
	while (x < map->images.draw->width)
	{
		if (grid_raycast(&hit, map, origin, calculate_ray_dir(map, x)) == 1)
			draw_wall(map, x, hit);
		x++;
	}
	return (1);
}
