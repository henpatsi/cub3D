/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/23 12:55:35 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_visuals(t_map *map)
{
	if (mlx_image_to_window(map->mlx, map->images.floor, 0,
			map->mlx->height / 2) == -1)
		return (-1);
	if (mlx_image_to_window(map->mlx, map->images.ceiling, 0, 0) == -1)
		return (-1);
	mlx_set_instance_depth(map->images.ceiling->instances, 0);
	mlx_set_instance_depth(map->images.floor->instances, 0);
	return (update_visuals(map));
}

int	update_visuals(t_map *map)
{
	t_player	player;

	player = map->player;

	mlx_instance_t	*south_instances = map->images.south->instances;
	
	// Move test wall
	int x;
	x = 0;
	while (x < map->width)
	{
		south_instances[map->grid[0][x].image_instances.south].y = map->mlx->height / 2 - map->images.south->height / 2;
		south_instances[map->grid[0][x].image_instances.south].x = map->mlx->width / 2 + (x - player.x) * 128;
		x++;
	}

	return (1);
}