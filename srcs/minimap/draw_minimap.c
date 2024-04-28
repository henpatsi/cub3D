/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:28:58 by ixu               #+#    #+#             */
/*   Updated: 2024/04/28 10:38:03 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_minimap *minimap, mlx_image_t *image)
{
	int	x;
	int	y;

	y = -1;
	while (++y < minimap->pixel_grid_len)
	{
		x = -1;
		while (++x < minimap->pixel_grid_len)
		{
			if (minimap->pixel_grid[y][x].type == EMPTY)
				mlx_put_pixel(image, x + PAD, y + PAD, BLACK);
			else if (minimap->pixel_grid[y][x].type == WALL)
				mlx_put_pixel(image, x + PAD, y + PAD, DARK_GREY);
			else if (minimap->pixel_grid[y][x].type == PLAYER)
				mlx_put_pixel(image, x + PAD, y + PAD, MAGENTA);
		}
	}
}

void	reload_and_draw_minimap(t_map *map,	mlx_image_t *image)
{
	init_minimap(map->minimap);
	load_minimap_grid(map);
	load_pixel_grid(map->minimap);
	draw_minimap(map->minimap, image);
}
