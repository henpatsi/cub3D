/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:35:01 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/14 10:25:16 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	gnl_error_exit(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == GNL_FD_ERROR)
		ft_putstr_fd("invalid fd\n", 2);
	else if (error == GNL_READ_ERROR)
		perror("read() error");
	else if (error == GNL_MALLOC_ERROR)
		ft_putstr_fd("malloc() error\n", 2);
	exit (1);
}

int	gnl_error_return(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == GNL_FD_ERROR)
		ft_putstr_fd("invalid fd\n", 2);
	else if (error == GNL_READ_ERROR)
		perror("read() error");
	else if (error == GNL_MALLOC_ERROR)
		ft_putstr_fd("malloc() error\n", 2);
	return (-1);
}

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
