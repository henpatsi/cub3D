/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/23 13:56:08 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_scaled_image(t_map *map, mlx_image_t *image, int x_pos, int y_pos, int scale)
{
	uint32_t	x;
	uint32_t	y;

	scale = 1;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel(map->images.draw, x + x_pos, y + y_pos, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

int	init_visuals(t_map *map)
{
	// Background
	if (mlx_image_to_window(map->mlx, map->images.floor, 0,
			map->mlx->height / 2) == -1)
		return (-1);
	if (mlx_image_to_window(map->mlx, map->images.ceiling, 0, 0) == -1)
		return (-1);
	mlx_set_instance_depth(map->images.ceiling->instances, 0);
	mlx_set_instance_depth(map->images.floor->instances, 0);

	// Test wall
	map->images.draw = mlx_new_image(map->mlx, map->mlx->width, map->mlx->height);
	mlx_image_to_window(map->mlx, map->images.draw, 0, 0);
	int x;
	x = 0;
	while (x < map->width)
	{
		//map->grid[0][x].image_instances.south = mlx_image_to_window(map->mlx, map->images.south, 0, 0);
		draw_scaled_image(map, map->images.south, map->mlx->width / 2 + (x - map->player.x) * 128,
				map->mlx->height / 2 - map->images.south->height / 2, 1);
		x++;
	}
	return (update_visuals(map));
}

int	update_visuals(t_map *map)
{
	//mlx_instance_t	*south_instances = map->images.south->instances;

	// Move test wall
	int x;
	x = 0;
	while (x < map->width)
	{
		// south_instances[map->grid[0][x].image_instances.south].y = map->mlx->height / 2 - map->images.south->height / 2;
		// south_instances[map->grid[0][x].image_instances.south].x = map->mlx->width / 2 + (x - player.x) * 128;
		draw_scaled_image(map, map->images.south, map->mlx->width / 2 + (x - map->player.x) * 128,
				map->mlx->height / 2 - map->images.south->height / 2, 1);
		x++;
	}

	return (1);
}