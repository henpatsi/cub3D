/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/24 12:19:53 by hpatsi           ###   ########.fr       */
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

	x = 0;
	while (x < map->images.draw->width)
	{
		double screen_center_offset = x - (double) (map->images.draw->width / 2);
		double grid_offset = screen_center_offset / 100;
		printf("x: %d, scroff: %f, grdoff: %f\n", x, screen_center_offset, grid_offset);

		y = 0;
		
		if (map->player.x + grid_offset >= 0 && map->player.x + grid_offset < map->width
				&& map->grid[0][(int)(map->player.x + grid_offset)].type == WALL)
		{
			uint32_t wall_height = 200 - (int) fabs(map->player.y - 0) * 10;
			uint32_t target = (map->images.draw->height / 2) - (wall_height / 2);
			while (y < target)
			{
				mlx_put_pixel(map->images.draw, x, y, map->ceiling_color);
				y++;
			}
			target += wall_height;
			while (y < target)
			{
				mlx_put_pixel(map->images.draw, x, y, 0xFF0000FF);
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