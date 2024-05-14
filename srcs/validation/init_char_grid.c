/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_char_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:19:17 by ixu               #+#    #+#             */
/*   Updated: 2024/05/20 09:52:50 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	fill_in_grid(char *line, t_map *map, char **grid, int row)
{
	int	col;

	col = 0;
	grid[row] = (char *)ft_calloc(sizeof(char), (map->width + 1));
	if (grid[row] == NULL)
	{
		ft_putstr_fd("malloc() error\n", 2);
		free_char_grid(grid);
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
	return (0);
}

static void	parse_file(int fd, int map_start_line, t_map *map, char **grid)
{
	char	*line;
	int		line_nbr;
	int		row;
	int		gnl_error;

	line_nbr = 0;
	row = 0;
	while (1)
	{
		line = get_next_line(fd, &gnl_error);
		line_nbr++;
		if (gnl_error != 0)
			gnl_error_free_and_exit(grid, row, gnl_error, fd);
		if (line == NULL)
			break ;
		if (line_nbr < map_start_line || ft_strcmp(line, "\n") == 0)
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

char	**init_char_grid(char *file, t_map *map, int map_start_line)
{
	char	**grid;
	int		fd;

	grid = (char **)ft_calloc(sizeof(char *), (map->height + 1));
	if (grid == NULL)
		put_error_and_exit("malloc() error\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_and_exit("open() error");
	grid = (char **)ft_calloc(sizeof(char *), (map->height + 1));
	if (grid == NULL)
		put_error_and_exit("malloc() error\n");
	parse_file(fd, map_start_line, map, grid);
	if (close(fd) == -1)
	{
		free_char_grid(grid);
		perror_and_exit("close() error");
	}
	return (grid);
}
