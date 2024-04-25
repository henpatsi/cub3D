/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:44:40 by ixu               #+#    #+#             */
/*   Updated: 2024/04/25 11:05:39 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	non_map_error(char *line, char **split_line)
{
	ft_putstr_fd("Error\nInvalid element: ", 2);
	ft_putstr_fd(line, 2);
	free(line);
	free_arr(split_line);
	exit(EXIT_FAILURE);
}

void	map_error(char *message, char **grid)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	free_grid(grid);
	exit(EXIT_FAILURE);
}

void	perror_and_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	put_error_and_exit(char *message)
{
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	put_error_free_and_exit(char *message, char **grid, int row)
{
	int	i;

	ft_putstr_fd(message, 2);
	i = 0;
	while (i < row)
	{
		free(grid[row]);
		i++;
	}
	free(grid);
	exit(EXIT_FAILURE);
}
