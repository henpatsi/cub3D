/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:44:10 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/20 09:51:33 by hpatsi           ###   ########.fr       */
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
	else
		ft_putstr_fd("unknown error\n", 2);
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
	else
		ft_putstr_fd("unknown error\n", 2);
	return (-1);
}

void	gnl_error_free_and_exit(char **grid, int row, int gnl_error, int fd)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	if (close(fd) == -1)
		perror("close() error");
	gnl_error_exit(gnl_error);
}

void	close_file_and_exit(int fd)
{
	if (close(fd) == -1)
		perror_and_exit("close() error");
	exit(EXIT_FAILURE);
}
