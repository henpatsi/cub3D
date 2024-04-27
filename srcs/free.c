/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:54:33 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/27 14:16:43 by ixu              ###   ########.fr       */
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

void	free_mini_grid(t_mini_gridpos **grid)
{
	int	y;

	y = 0;
	while (grid[y] != NULL)
	{
		free(grid[y]);
		y++;
	}
	free(grid);
}
