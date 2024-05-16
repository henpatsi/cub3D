/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:35:01 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/16 12:19:22 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	return_error(char *message)
{
	if (message != 0)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	return (-1);
}

void	put_error_and_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	perror_and_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	perror(message);
	exit(EXIT_FAILURE);
}

void	non_map_error(char *message, char *line, char **split_line, int fd)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(line, 2);
	free(line);
	ft_freestrs(split_line);
	if (close(fd) == -1)
		perror("close() error");
	exit(EXIT_FAILURE);
}

void	map_error(char *message, char **grid)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	free_char_grid(grid);
	exit(EXIT_FAILURE);
}
