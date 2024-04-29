/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:12:43 by ixu               #+#    #+#             */
/*   Updated: 2024/04/29 13:49:44 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_minimap_grid(t_gridpos **grid, int len)
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

void	init_minimap(t_minimap *minimap)
{
	init_minimap_grid(minimap->grid, minimap->len);
	init_minimap_grid(minimap->pixel_grid, minimap->pixel_grid_len);
}
