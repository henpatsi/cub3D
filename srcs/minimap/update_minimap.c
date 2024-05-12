/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:12:43 by ixu               #+#    #+#             */
/*   Updated: 2024/05/12 18:18:25 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	reset_minimap_grid(t_gridpos **grid, int len)
{
	int	y;
	int	x;

	y = -1;
	while (++y < len)
	{
		x = -1;
		while (++x < len)
			grid[y][x].type = EMPTY;
	}
}

static void	reset_minimap(t_minimap *minimap)
{
	reset_minimap_grid(minimap->grid, minimap->len);
	reset_minimap_grid(minimap->pixel_grid, minimap->pixel_grid_len);
}

void	update_minimap(t_map *map)
{
	reset_minimap(&map->minimap);
	load_minimap_grid(map);
	load_pixel_grid(&map->minimap);
	draw_minimap(map);
}
