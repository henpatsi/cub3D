/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:17:11 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/13 10:40:54 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_map(t_map *map, char *map_filename)
{
	int	map_fd;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd == -1)
		exit_error("Failed to open map");
	map->textures.closed_door = mlx_load_png(CLOSED_DOOR_TEXTURE);
	map->textures.door_sides = mlx_load_png(DOOR_SIDES_TEXTURE);
	if (map->textures.closed_door == 0 || map->textures.door_sides == 0
		|| load_config(map, map_fd) == -1)
	{
		close(map_fd);
		free_textures(map->textures);
		exit(1);
	}
	if (load_grid(map, map_fd) == -1)
	{
		close(map_fd);
		free_textures(map->textures);
		exit(1);
	}
	close(map_fd);
	return (1);
}
