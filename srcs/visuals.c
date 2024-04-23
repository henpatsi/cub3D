/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/23 12:40:53 by hpatsi           ###   ########.fr       */
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
	south_instances[map->grid[0][0].image_instances.south].y = map->mlx->height / 2 - map->images.south->height / 2;
	south_instances[map->grid[0][1].image_instances.south].y = map->mlx->height / 2 - map->images.south->height / 2;
	south_instances[map->grid[0][2].image_instances.south].y = map->mlx->height / 2 - map->images.south->height / 2;
	south_instances[map->grid[0][3].image_instances.south].y = map->mlx->height / 2 - map->images.south->height / 2;
	south_instances[map->grid[0][4].image_instances.south].y = map->mlx->height / 2 - map->images.south->height / 2;

	south_instances[map->grid[0][0].image_instances.south].x = (0 - player.x) * 128;
	south_instances[map->grid[0][1].image_instances.south].x = (1 - player.x) * 128;
	south_instances[map->grid[0][2].image_instances.south].x = (2 - player.x) * 128;
	south_instances[map->grid[0][3].image_instances.south].x = (3 - player.x) * 128;
	south_instances[map->grid[0][4].image_instances.south].x = (4 - player.x) * 128;

	return (1);
}