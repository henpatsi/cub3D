/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:07:22 by ixu               #+#    #+#             */
/*   Updated: 2024/05/15 15:38:25 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_char_grid(char **grid, t_map *map)
{
	int	r;
	int	c;

	printf("map width: %d\n", map->width);
	printf("map height: %d\n", map->height);
	r = -1;
	while (++r < map->height)
	{
		c = -1;
		while (++c < map->width)
		{
			if (grid[r][c] == ' ' || grid[r][c] == '0')
				printf("%c", '.');
			else if (grid[r][c] == '1')
				printf("%c", '#');
			else if (grid[r][c] == '2')
				printf("%c", 'D');
			else
				printf("%c", grid[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}

static void	print_minimap_grid(t_gridpos **grid, int len)
{
	int	y;
	int	x;

	printf("%d\n", len);
	y = -1;
	while (++y < len)
	{
		x = -1;
		while (++x < len)
		{
			if (grid[y][x].type == WALL)
				printf("%c", '#');
			else if (grid[y][x].type == EMPTY)
				printf("%c", '.');
			else if (grid[y][x].type == CLOSED_DOOR)
				printf("%c", 'D');
			else if (grid[y][x].type == PLAYER)
				printf("%c", 'P');
		}
		printf("\n");
	}
	printf("\n");
}

void	print_minimap(t_minimap *minimap, bool scaled_up)
{
	int			len;
	t_gridpos	**grid;

	if (!scaled_up)
	{
		len = minimap->len;
		grid = minimap->grid;
		printf("Original minimap length: ");
	}
	else
	{
		len = minimap->pixel_grid_len;
		grid = minimap->pixel_grid;
		printf("Enlarged minimap length: ");
	}
	print_minimap_grid(grid, len);
}
