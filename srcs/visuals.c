/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/25 15:10:43 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int	init_visuals(t_map *map)
{
	// Canvas for drawing
	map->images.draw = mlx_new_image(map->mlx, map->mlx->width, map->mlx->height);
	mlx_image_to_window(map->mlx, map->images.draw, 0, 0);
	mlx_set_instance_depth(map->images.draw->instances, 1);

	return (update_visuals(map));
}

int	update_visuals(t_map *map)
{
	uint32_t x;
	uint32_t y;

	t_hitinfo 	hit;
	t_vector	origin;
	origin.x = map->player.x;
	origin.y = map->player.y;
	if (grid_raycast(&hit, map, origin, map->player.dir) == 1)
		printf("hit wall, distance: %f, side: %d\n", hit.distance, hit.side);

	x = 0;
	while (x < map->images.draw->width)
	{
		t_vector ray_dir;
		double screen_position = 2 * (double) x / (double) map->images.draw->width - 1;
		ray_dir.x = map->player.dir.x + map->player.cam_plane.x * screen_position;
		ray_dir.y = map->player.dir.y + map->player.cam_plane.y * screen_position;
		//printf("ray dir x: %f, y: %f\n", ray_dir.x, ray_dir.y);

		y = 0;
		uint32_t color;
		if (hit.side == NORTH)
			color = 0xFF0000FF;
		if (hit.side == SOUTH)
			color = 0x00FF00FF;
		if (hit.side == EAST)
			color = 0x0000FFFF;
		if (hit.side == WEST)
			color = 0xFF00FFFF;

		if (grid_raycast(&hit, map, origin, ray_dir) == 1)
		{
			uint32_t wall_height = 200 - hit.distance * 3;
			uint32_t target = (map->images.draw->height / 2) - (wall_height / 2);
			while (y < target)
			{
				mlx_put_pixel(map->images.draw, x, y, map->ceiling_color);
				y++;
			}
			target += wall_height;
			while (y < target)
			{
				mlx_put_pixel(map->images.draw, x, y, color);
				y++;
			}
			while (y < map->images.draw->height)
			{
				mlx_put_pixel(map->images.draw, x, y, map->floor_color);
				y++;
			}
		}
		else
		{
			while (y < 200 + 100 / 2)
			{
				mlx_put_pixel(map->images.draw, x, y, map->ceiling_color);
				y++;
			}
			while (y < map->images.draw->height)
			{
				mlx_put_pixel(map->images.draw, x, y, map->floor_color);
				y++;
			}
		}
		
		x++;
	}

	return (1);
}