/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:09 by ixu               #+#    #+#             */
/*   Updated: 2024/04/25 11:13:26 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_closed(int r, int c, t_map *map, char **grid)
{
	if (r < 0 || r >= map->height || c < 0 || c >= map->width)
		return (false);
	if (grid[r][c] == ' ')
		return (false);
	return (true);
}

static void	validate_walls(char **grid, t_map *map)
{
	int	r;
	int	c;

	r = 0;
	while (r < map->height)
	{
		c = 0;
		while (c < map->width)
		{
			if (grid[r][c] == '0' || ft_strchr("NSEW", grid[r][c]) != NULL)
			{
				if (!is_closed(r + 1, c, map, grid))
					map_error("Map not closed by walls\n", grid);
				if (!is_closed(r - 1, c, map, grid))
					map_error("Map not closed by walls\n", grid);
				if (!is_closed(r, c + 1, map, grid))
					map_error("Map not closed by walls\n", grid);
				if (!is_closed(r, c - 1, map, grid))
					map_error("Map not closed by walls\n", grid);
			}
			c++;
		}
		r++;
	}
}

void	validate_map(char **grid, t_map *map)
{
	int		row;
	int		col;
	bool	player_found;

	row = 0;
	player_found = false;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (ft_strchr("01NSEW ", grid[row][col]) == NULL)
				map_error("Map contains an invalid character\n", grid);
			if (ft_strchr("NSEW", grid[row][col]) != NULL && !player_found)
				player_found = true;
			else if (ft_strchr("NSEW", grid[row][col]) != NULL && player_found)
				map_error("Map contains more than one start position\n", grid);
			col++;
		}
		row++;
	}
	if (!player_found)
		map_error("Map missing start position\n", grid);
	validate_walls(grid, map);
}
