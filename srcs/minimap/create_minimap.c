/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:48:51 by ixu               #+#    #+#             */
/*   Updated: 2024/04/29 12:20:34 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_minimap_grid(t_map *map, t_minimap *minimap)
{
	int	y;

	minimap->len = D * 2 + 1;
	minimap->grid = ft_calloc(minimap->len + 1, sizeof(t_mini_gridpos *));
	if (minimap->grid == NULL)
		return (return_error("malloc() error"));
	y = -1;
	while (++y < minimap->len)
	{
		minimap->grid[y] = ft_calloc(minimap->len + 1, sizeof(t_mini_gridpos));
		if (minimap->grid[y] == NULL)
		{
			free_mini_grid(minimap->grid);
			return (return_error("malloc() error"));
		}
	}
	load_minimap_grid(map);
	if (DEBUG_MODE)
		print_minimap(minimap, false);
	return (0);
}

int	create_minimap_pixel_grid(t_minimap *minimap)
{
	int				new_len;
	int				y;

	new_len = minimap->len * SCALE;
	minimap->pixel_grid = ft_calloc(new_len + 1, sizeof(t_mini_gridpos *));
	if (minimap->pixel_grid == NULL)
	{
		free_mini_grid(minimap->grid);
		return (return_error("malloc() error"));
	}
	y = -1;
	while (++y < new_len)
	{
		minimap->pixel_grid[y] = ft_calloc(new_len + 1, sizeof(t_mini_gridpos));
		if (minimap->pixel_grid[y] == NULL)
		{
			free_mini_grid(minimap->grid);
			free_mini_grid(minimap->pixel_grid);
			return (return_error("malloc() error"));
		}
	}
	load_pixel_grid(minimap);
	if (DEBUG_MODE)
		print_minimap(minimap, true);
	return (0);
}
