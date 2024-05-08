/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:17:11 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/08 22:13:11 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* int	count_doors(t_gridpos **grid)
{
	int	x;
	int	y;
	int	door_count;

	door_count = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (grid[y][x].type == DOOR)
				door_count++;
		}
	}
	return (door_count);
} */

int	load_map(t_map *map, char *map_filename)
{
	int	map_fd;
	// int	i;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd == -1)
		exit_error("Failed to open map");
	if (load_config(map, map_fd) == -1)
	{
		close(map_fd);
		exit(1);
	}
	if (load_grid(map, map_fd) == -1)
	{
		close(map_fd);
		free_textures(map->textures);
		exit(1);
	}
	close(map_fd);
	// map->door_count = count_doors(map->grid);
	// printf("door count: %d\n", map->door_count);
	// map->doors = ft_calloc(map->door_count, sizeof(t_door));
	// if (map->doors == NULL)
	// {
	// 	;
	// }
	// i = -1;
	// while (++i < map->door_count)
	// {
	// 	map->doors[i].door_open = false;
	// }
	return (1);
}
