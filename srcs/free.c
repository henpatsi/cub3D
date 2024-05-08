/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:54:33 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/08 10:27:25 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

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
