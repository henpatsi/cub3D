/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:52:45 by ixu               #+#    #+#             */
/*   Updated: 2024/04/30 14:17:19 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_minimap_grid(t_map *map)
{
	int	y;
	int	x;
	int	my;
	int	mx;

	y = (int)map->player.y - D;
	my = 0;
	while (y >= (int)map->player.y - D && y <= (int)map->player.y + D)
	{
		if (y >= 0 && y < map->height)
		{
			x = (int)map->player.x - D;
			mx = 0;
			while (x >= (int)map->player.x - D && x <= (int)map->player.x + D)
			{
				if (x >= 0 && x < map->width)
					map->minimap.grid[my][mx].type = map->grid[y][x].type;
				x++;
				mx++;
			}
		}
		y++;
		my++;
	}
	map->minimap.grid[D][D].type = PLAYER;
}

void	load_pixel_grid(t_minimap *minimap)
{
	int			my;
	int			mx;
	int			py;
	int			px;
	t_gridpos	**pixel_grid;

	pixel_grid = minimap->pixel_grid;
	my = -1;
	while (++my < minimap->len)
	{
		mx = -1;
		while (++mx < minimap->len)
		{
			py = my * SCALE - 1;
			while (++py < (my + 1) * SCALE)
			{
				px = mx * SCALE - 1;
				while (++px < (mx + 1) * SCALE)
					pixel_grid[py][px].type = minimap->grid[my][mx].type;
			}
		}
	}
	minimap->pixel_grid_len = minimap->len * SCALE;
}
