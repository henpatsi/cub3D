/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:22:00 by ixu               #+#    #+#             */
/*   Updated: 2024/05/15 21:09:08 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_start(bool *player_found, t_vector *start_pos, int r, int c)
{
	*player_found = true;
	start_pos->x = (double)c;
	start_pos->y = (double)r;
}

static bool	is_closed(int row, int col, t_map *map, char **grid)
{
	if (row < 0 || row >= map->height || col < 0 || col >= map->width
		|| grid[row][col] == ' ')
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
			if (grid[r][c] == '0' || ft_strchr("NSEW", grid[r][c]) != NULL
				|| grid[r][c] == '2')
			{
				if (!is_closed(r + 1, c, map, grid)
					|| !is_closed(r - 1, c, map, grid)
					|| !is_closed(r, c + 1, map, grid)
					|| !is_closed(r, c - 1, map, grid))
					map_error("Map not closed by walls\n", grid);
			}
			if (grid[r][c] == '2')
				check_door_position(r, c, map, grid);
			c++;
		}
		r++;
	}
}

static void	check_map_islands(char **grid, t_map *map, t_vector start_pos)
{
	int	row;
	int	col;

	flood_fill(grid, map, (int)start_pos.y, (int)start_pos.x);
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (ft_strchr("012", grid[row][col]) != NULL)
				map_error("Map separated by one or more spaces/lines\n", grid);
			col++;
		}
		row++;
	}
}

void	validate_map(char **grid, t_map *map)
{
	int			row;
	int			col;
	bool		player_found;
	t_vector	start_pos;

	row = -1;
	player_found = false;
	start_pos = (t_vector){0, 0};
	while (++row < map->height)
	{
		col = -1;
		while (++col < map->width)
		{
			if (ft_strchr("012NSEW ", grid[row][col]) == NULL)
				map_error("Map contains an invalid character\n", grid);
			if (ft_strchr("NSEW", grid[row][col]) != NULL && !player_found)
				set_start(&player_found, &start_pos, row, col);
			else if (ft_strchr("NSEW", grid[row][col]) != NULL && player_found)
				map_error("Map contains more than one start position\n", grid);
		}
	}
	if (!player_found)
		map_error("Map missing start position\n", grid);
	validate_walls(grid, map);
	check_map_islands(grid, map, start_pos);
}
