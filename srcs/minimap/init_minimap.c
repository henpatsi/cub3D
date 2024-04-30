/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:48:51 by ixu               #+#    #+#             */
/*   Updated: 2024/04/30 15:37:29 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	create_minimap_grid(t_map *map, t_minimap *minimap)
{
	int	y;

	minimap->len = D * 2 + 1;
	minimap->grid = ft_calloc(minimap->len + 1, sizeof(t_gridpos *));
	if (minimap->grid == NULL)
		return (return_error("malloc() error"));
	y = -1;
	while (++y < minimap->len)
	{
		minimap->grid[y] = ft_calloc(minimap->len + 1, sizeof(t_gridpos));
		if (minimap->grid[y] == NULL)
		{
			free_grid(minimap->grid);
			return (return_error("malloc() error"));
		}
	}
	load_minimap_grid(map);
	if (DEBUG_MODE)
		print_minimap(minimap, false);
	return (0);
}

static int	create_minimap_pixel_grid(t_minimap *minimap)
{
	int				new_len;
	int				y;

	new_len = minimap->len * SCALE;
	minimap->pixel_grid = ft_calloc(new_len + 1, sizeof(t_gridpos *));
	if (minimap->pixel_grid == NULL)
	{
		free_grid(minimap->grid);
		return (return_error("malloc() error"));
	}
	y = -1;
	while (++y < new_len)
	{
		minimap->pixel_grid[y] = ft_calloc(new_len + 1, sizeof(t_gridpos));
		if (minimap->pixel_grid[y] == NULL)
		{
			free_grid(minimap->grid);
			free_grid(minimap->pixel_grid);
			return (return_error("malloc() error"));
		}
	}
	load_pixel_grid(minimap);
	if (false)
		print_minimap(minimap, true);
	return (0);
}

int	init_minimap(t_map *map)
{
	if (create_minimap_grid(map, &map->minimap) == -1)
		return (-1);
	if (create_minimap_pixel_grid(&map->minimap) == -1)
		return (-1);
	draw_minimap(map, map->images.draw);
	return (0);
}
