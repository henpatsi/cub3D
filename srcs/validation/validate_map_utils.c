/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:50:28 by ixu               #+#    #+#             */
/*   Updated: 2024/05/15 15:34:12 by ixu              ###   ########.fr       */
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

static void	check_neighbor_tiles(char **grid, t_map *map, int *top, int (*stack)[2])
{
	int	dr[] = {-1, 1, 0, 0};
	int	dc[] = {0, 0, -1, 1};
	int	r;
	int	c;
	int	d;
	int	nr;
	int	nc;

	r = stack[*top][0];
	c = stack[*top][1];
	// printf("visited: (%d, %d)\n", r, c);
	d = 0;
	while (d < 4)
	{
		nr = r + dr[d];
		nc = c + dc[d];
		if (nr >= 0 && nr < map->height && nc >= 0 && nc < map->width
			&& grid[nr][nc] != '*' && grid[nr][nc] != ' ')
		{
			stack[*top][0] = nr;
			stack[*top][1] = nc;
			*top += 1;
			grid[nr][nc] = '*';
		}
		d++;
	}
}

void	flood_fill(char **grid, t_map *map, int row, int col)
{
	int	(*stack)[2];
	int	top;

	stack = ft_calloc(map->height * map->width, sizeof(int[2]));
	if (stack == NULL)
	{
		ft_putstr_fd("malloc() error\n", 2);
		free_char_grid(grid);
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
