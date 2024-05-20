/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:35:49 by ixu               #+#    #+#             */
/*   Updated: 2024/05/20 10:20:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static void	init_directions(int *dr, int *dc)
{
	dr[0] = -1;
	dr[1] = 1;
	dr[2] = 0;
	dr[3] = 0;
	dc[0] = 0;
	dc[1] = 0;
	dc[2] = -1;
	dc[3] = 1;
}

static void	check_neighbor_tiles(char **grid, t_map *map, int *top, \
			int (*stack)[2])
{
	int			dr[4];
	int			dc[4];
	t_coords	current;
	t_coords	neighbor;
	int			d;

	init_directions(dr, dc);
	current.r = stack[*top][0];
	current.c = stack[*top][1];
	d = -1;
	while (++d < 4)
	{
		neighbor.r = current.r + dr[d];
		neighbor.c = current.c + dc[d];
		if (neighbor.r >= 0 && neighbor.r < map->height
			&& neighbor.c >= 0 && neighbor.c < map->width
			&& grid[neighbor.r][neighbor.c] != '*'
			&& grid[neighbor.r][neighbor.c] != ' ')
		{
			stack[*top][0] = neighbor.r;
			stack[*top][1] = neighbor.c;
			*top += 1;
			grid[neighbor.r][neighbor.c] = '*';
		}
	}
}

void	flood_fill(char **grid, t_map *map, int row, int col)
{
	int	(*stack)[2];
	int	top;

	stack = ft_calloc(map->height * map->width, sizeof(int [2]));
	if (stack == NULL)
	{
		ft_putstr_fd("malloc() error\n", 2);
		ft_freestrs(grid);
		exit(EXIT_FAILURE);
	}
	top = 0;
	stack[top][0] = row;
	stack[top][1] = col;
	top++;
	grid[row][col] = '*';
	while (top > 0)
	{
		top--;
		check_neighbor_tiles(grid, map, &top, stack);
	}
	free(stack);
}
