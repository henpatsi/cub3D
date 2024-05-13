/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:44:40 by ixu               #+#    #+#             */
/*   Updated: 2024/05/12 22:37:59 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	non_map_error(char *message, char *line, char **split_line)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(line, 2);
	free(line);
	ft_freestrs(split_line);
	exit(EXIT_FAILURE);
}

void	map_error(char *message, char **grid)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	free_char_grid(grid);
	exit(EXIT_FAILURE);
}

void	perror_and_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	perror(message);
	exit(EXIT_FAILURE);
}

void	put_error_and_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	put_error_free_and_exit(char *message, char **grid, int row)
{
	int	i;

	ft_putstr_fd("Error\n", 2);
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
