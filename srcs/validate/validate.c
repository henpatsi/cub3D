/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:27:31 by ixu               #+#    #+#             */
/*   Updated: 2024/05/13 12:26:23 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_file_extension(char *file)
{
	if (ft_strlen(file) < 5)
	{
		ft_putendl_fd("Invalid filename", 2);
		ft_putendl_fd("Usage: ./cub3D path_to_file.cub", 1);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(file + ft_strlen(file) - 4, ".cub") != 0)
	{
		ft_putendl_fd("Invalid filename", 2);
		ft_putendl_fd("Usage: ./cub3D path_to_file.cub", 1);
		exit(EXIT_FAILURE);
	}
}

static int	parse_file(int fd, t_map *map, int *flags)
{
	int		last_line_before_map;
	char	*line;

	// int line_nbr = 0;
	last_line_before_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		// line_nbr++;
		if (line == NULL)
			break ;
		// printf("line %3d: %s", line_nbr, line);
		if (!map_started(*flags))
			last_line_before_map++;
		if (*line == '\n' && !map_started(*flags))
		{
			free(line);
			continue ;
		}
		if (!map_started(*flags))
			validate_non_map_elements(line, flags);
		else
			get_map_dimensions(line, map);
		free(line);
	}
	return (last_line_before_map + 1);
}

static void	print_grid(char **grid, t_map *map)
{
	int	r;
	int	c;

	ft_printf("map width: %d\n", map->width);
	ft_printf("map height: %d\n", map->height);
	r = -1;
	while (++r < map->height)
	{
		c = -1;
		while (++c < map->width)
		{
			if (grid[r][c] == ' ')
				ft_printf("%c", '-');
			else
				ft_printf("%c", grid[r][c]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
}

/*
	During the first time of reading lines of the file, 
	(1) non-map elements are validated, (2) map dimensions 
	(width and height) are obtained.

	During the second time of reading lines of the file, 
	the map content is saved to a 2D array (grid).
	Then map validation is handled with the grid.
*/

static void	validate_file_content(char *file, t_map *map)
{
	int		fd;
	int		flags;
	int		map_start_line;
	char	**grid;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_and_exit("open() error");
	map->width = 0;
	map->height = 0;
	flags = 0;
	map_start_line = parse_file(fd, map, &flags);
	if (close(fd) == -1)
		perror_and_exit("close() error");
	if (map_start_line == 1 || !map_started(flags))
		put_error_and_exit("Empty file, or file contains only newline \
character, or error occurred when reading the file\n");
	grid = grid_init(file, map, map_start_line);
	validate_map(grid, map);
	if (DEBUG_MODE)
		print_grid(grid, map);
	free_char_grid(grid);
}

void	validate_input(int argc, char **argv, t_map *map)
{
	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		ft_putendl_fd("Usage: ./cub3D path_to_file.cub", 1);
		exit(EXIT_FAILURE);
	}
	validate_file_extension(argv[1]);
	validate_file_content(argv[1], map);
}
