/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:50:28 by ixu               #+#    #+#             */
/*   Updated: 2024/04/26 15:12:16 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_closed(int row, int col, t_map *map, char **grid)
{
	if (row < 0 || row >= map->height || col < 0 || col >= map->width
		|| grid[row][col] == ' ')
		return (false);
	return (true);
}

void	flood_fill(char **grid, t_map *map, int row, int col)
{
	if (row < 0 || row >= map->height || col < 0 || col >= map->width
		|| ft_strchr("P#. ", grid[row][col]) != NULL)
		return ;
	if (ft_strchr("NSEW", grid[row][col]) != NULL)
		grid[row][col] = 'P';
	else if (grid[row][col] == '1')
		grid[row][col] = '#';
	else
		grid[row][col] = '.';
	flood_fill(grid, map, row + 1, col);
	flood_fill(grid, map, row - 1, col);
	flood_fill(grid, map, row, col + 1);
	flood_fill(grid, map, row, col - 1);
}
