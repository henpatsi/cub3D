/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:17:11 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/20 09:55:24 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_door_textures(t_map *map)
{
	map->textures.closed_door = mlx_load_png(CLOSED_DOOR_TEXTURE);
	map->textures.door_sides = mlx_load_png(DOOR_SIDES_TEXTURE);
	if (map->textures.closed_door == 0 || map->textures.door_sides == 0)
		return (-1);
	return (1);
}

int	load_map(t_map *map, char *map_filename)
{
	int	map_fd;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd == -1)
		perror_and_exit("open() error");
	if (load_door_textures(map) == -1 || load_config(map, map_fd) == -1
		|| load_grid(map, map_fd) == -1)
	{
		free_textures(map->textures);
		if (close(map_fd) == -1)
			perror("close() error");
		exit(1);
	}
	if (close(map_fd) == -1)
	{
		perror("close() error");
		free_textures(map->textures);
		free_grid(map->grid);
		exit(1);
	}
	return (1);
}
