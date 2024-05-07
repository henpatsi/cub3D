/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:17:11 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/07 10:44:39 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_map(t_map *map, char *map_filename)
{
	int	map_fd;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd == -1)
		return_error("Failed to open map");
	if (load_config(map, map_fd) == -1)
		return (-1);
	if (load_grid(map, map_fd) == -1)
	{
		free_textures(map->textures);
		return (-1);
	}
	close(map_fd);
	if (load_animations(map->mlx, &map->animation) == -1)
	{
		free_grid(map->grid);
		free_textures(map->textures);
		return (-1);
	}
	return (1);
}
