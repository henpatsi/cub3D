/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/29 14:04:49 by hpatsi           ###   ########.fr       */
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

	int image_x = round(hit.side_ratio * (double) wall_image->width);
	
	if (scaled_wall_height >= map->images.draw->height)
	{
		uint32_t y = 0;
		while(y < map->images.draw->height)
		{
			mlx_put_pixel(map->images.draw, start.x, start.y + y, 0x000000FF); // temp black wall
			y++;
		}
	}
	else
	{
		draw_vertical_line(map, start, (map->images.draw->height / 2) - (scaled_wall_height / 2), map->ceiling_color);
		start.y += (map->images.draw->height / 2) - (scaled_wall_height / 2);

		uint32_t y = 0;
		while(y < scaled_wall_height)
		{
			int image_y = round((double) y / (double) scaled_wall_height * (double) wall_image->height);

			int image_x_offset = image_x * 4;
			int image_y_offset = image_y * wall_image->width * 4;

			uint32_t color;
			uint32_t color2;
			uint8_t	byte[4];
			ft_memcpy(&color, &wall_image->pixels[image_y_offset + image_x_offset], 4);

			byte[0] = (color >> 24) & 0xFF;
			byte[1] = (color >> 16) & 0xFF;
			byte[2] = (color >> 8) & 0xFF;
			byte[3] = (color) & 0xFF;
			color2 = byte[3];
			color2 = color2 << 8;
			color2 += byte[2];
			color2 = color2 << 8;
			color2 += byte[1];
			color2 = color2 << 8;
			color2 += byte[0];

			mlx_put_pixel(map->images.draw, start.x, start.y + y, (uint32_t) color2);
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
