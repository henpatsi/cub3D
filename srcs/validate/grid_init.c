/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:19:17 by ixu               #+#    #+#             */
/*   Updated: 2024/05/12 21:04:21 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	fill_in_grid(char *line, t_map *map, char **grid, int row)
{
	int	col;

	col = 0;
	grid[row] = (char *)malloc(sizeof(char) * (map->width + 1));
	if (grid[row] == NULL)
	{
		ft_putstr_fd("malloc() error\n", 2);
		free_initial_grid(grid);
		free(line);
		return (1);
	}
	while (col < map->width && (line[col] != '\n' && line[col] != '\0'))
	{
		grid[row][col] = line[col];
		col++;
	}
	while (col < map->width)
	{
		grid[row][col] = ' ';
		col++;
	}
	grid[row][col] = '\0';
	return (0);
}

static void	close_file_and_exit(int fd)
{
	if (close(fd) == -1)
		perror_and_exit("close() error");
	exit(EXIT_FAILURE);
}

static void	parse_file(int fd, int map_start_line, t_map *map, char **grid)
{
	char	*line;
	int		line_nbr;
	int		row;

	line_nbr = 0;
	row = 0;
	while (1)
	{
		line = get_next_line(fd);
		line_nbr++;
		if (line == NULL && row == map->height)
			break ;
		else if (line == NULL && row != map->height)
			put_error_free_and_exit("Error occurred when reading the file\n", \
				grid, row);
		if (line_nbr < map_start_line)
		{
			free(line);
			continue ;
		}
		if (fill_in_grid(line, map, grid, row))
			close_file_and_exit(fd);
		row++;
		free(line);
	}
}

char	**grid_init(char *file, t_map *map, int map_start_line)
{
	char	**grid;
	int		fd;

	grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (grid == NULL)
		put_error_and_exit("malloc() error\n");
	grid[map->height] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(grid);
		perror_and_exit("open() error");
	}
	parse_file(fd, map_start_line, map, grid);
	if (close(fd) == -1)
		perror_and_exit("close() error");
	return (grid);
}
