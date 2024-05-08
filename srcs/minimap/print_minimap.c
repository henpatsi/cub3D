/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:51:02 by ixu               #+#    #+#             */
/*   Updated: 2024/05/08 22:01:31 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	print_minimap_grid(t_gridpos **grid, int len)
{
	int	y;
	int	x;

	ft_printf("%d\n", len);
	y = -1;
	while (++y < len)
	{
		x = -1;
		while (++x < len)
		{
			if (grid[y][x].type == WALL)
				ft_printf("%c", '#');
			else if (grid[y][x].type == EMPTY)
				ft_printf("%c", '.');
			else if (grid[y][x].type == CLOSED_DOOR)
				ft_printf("%c", 'D');
			else if (grid[y][x].type == PLAYER)
				ft_printf("%c", 'P');
		}
		ft_printf("\n");
	}
	ft_printf("\n");
}

void	print_minimap(t_minimap *minimap, bool scaled_up)
{
	int			len;
	t_gridpos	**grid;

	if (!scaled_up)
	{
		len = minimap->len;
		grid = minimap->grid;
		ft_printf("Original minimap length: ");
	}
	else
	{
		len = minimap->pixel_grid_len;
		grid = minimap->pixel_grid;
		ft_printf("Enlarged minimap length: ");
	}
	print_minimap_grid(grid, len);
}
