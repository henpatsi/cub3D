/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:54:33 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/15 09:37:59 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_grid(t_gridpos **grid)
{
	int	row;

	if (grid == 0)
		return ;
	row = 0;
	while (grid[row] != NULL)
	{
		free(grid[row]);
		row++;
	}
	free(grid);
}

void	free_char_grid(char **grid)
{
	int	row;

	if (grid == 0)
		return ;
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

void	free_animations(t_anim *animations)
{
	free(animations[0].images);
}

void	free_all(t_map *map)
{
	free_grid(map->grid);
	free_grid(map->minimap.grid);
	free_grid(map->minimap.pixel_grid);
	free_textures(map->textures);
	free_animations(map->animations);
}
