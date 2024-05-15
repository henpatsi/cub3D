/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:35:49 by ixu               #+#    #+#             */
/*   Updated: 2024/05/15 12:19:42 by ixu              ###   ########.fr       */
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

static bool	is_wall(int row, int col, t_map *map, char **grid)
{
	if (row < 0 || row >= map->height || col < 0 || col >= map->width)
		return (false);
	if (grid[row][col] == '1')
		return (true);
	return (false);
}

void	check_door_position(int r, int c, t_map *map, char **grid)
{
	if (is_wall(r + 1, c, map, grid))
	{
		if (!is_wall(r - 1, c, map, grid) || is_wall(r, c + 1, map, grid)
			|| is_wall(r, c - 1, map, grid))
			map_error("A door is positioned at a wrong tile\n", grid);
	}
	else
	{
		if (is_wall(r - 1, c, map, grid) || !is_wall(r, c + 1, map, grid)
			|| !is_wall(r, c - 1, map, grid))
			map_error("A door is positioned at a wrong tile\n", grid);
	}
}

void	flood_fill(char **grid, t_map *map, int row, int col)
{
	if (row < 0 || row >= map->height || col < 0 || col >= map->width
		|| ft_strchr("P#D. ", grid[row][col]) != NULL)
		return ;
	if (ft_strchr("NSEW", grid[row][col]) != NULL)
		grid[row][col] = 'P';
	else if (grid[row][col] == '1')
		grid[row][col] = '#';
	else if (grid[row][col] == '2')
		grid[row][col] = 'D';
	else
		grid[row][col] = '.';
	flood_fill(grid, map, row + 1, col);
	flood_fill(grid, map, row - 1, col);
	flood_fill(grid, map, row, col + 1);
	flood_fill(grid, map, row, col - 1);
}
