/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:44:10 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/15 09:35:18 by hpatsi           ###   ########.fr       */
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

void	gnl_error_free_and_exit(int fd, char **grid, int gnl_error)
{
	if (close(fd) == -1)
		perror_and_exit("close() error");
	free_char_grid(grid);
	gnl_error_exit(gnl_error);
}

void	close_file_and_exit(int fd)
{
	if (close(fd) == -1)
		perror_and_exit("close() error");
	exit(EXIT_FAILURE);
}
