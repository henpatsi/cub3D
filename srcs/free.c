/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:54:33 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/12 17:29:52 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_grid(t_gridpos **grid)
{
	int	y;

	y = 0;
	while (grid[y] != 0)
	{
		free(grid[y]);
		y++;
	}
	free(grid);
}

void	free_initial_grid(char **grid)
{
	int	row;

	row = 0;
	while (grid[row] != NULL)
	{
		free(grid[row]);
		row++;
	}
	free(grid);
}

void	free_textures(t_textures textures)
{
	if (textures.north)
		mlx_delete_texture(textures.north);
	if (textures.south)
		mlx_delete_texture(textures.south);
	if (textures.east)
		mlx_delete_texture(textures.east);
	if (textures.west)
		mlx_delete_texture(textures.west);
	if (textures.closed_door)
		mlx_delete_texture(textures.closed_door);
	if (textures.door_sides)
		mlx_delete_texture(textures.door_sides);
}

void	free_animation(t_anim *animation)
{
	free(animation->images);
}

void	free_all(t_map *map)
{
	free_grid(map->grid);
	free_grid(map->minimap.grid);
	free_grid(map->minimap.pixel_grid);
	free_textures(map->textures);
	free_animation(&map->animation);
}
