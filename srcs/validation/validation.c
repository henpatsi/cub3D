/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:27:31 by ixu               #+#    #+#             */
/*   Updated: 2024/05/16 12:16:44 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_file_extension(char *file)
{
	if (ft_strlen(file) < 5
		|| ft_strcmp(file + ft_strlen(file) - 4, ".cub") != 0)
	{
		ft_putendl_fd("Error\nInvalid filename", 2);
		ft_putendl_fd("Usage: ./cub3D path_to_file.cub", 1);
		exit(EXIT_FAILURE);
	}
	else if (file[ft_strlen(file) - 5] == '/')
	{
		ft_putendl_fd("Error\nInvalid filename", 2);
		ft_putendl_fd("Usage: ./cub3D path_to_file.cub", 1);
		exit(EXIT_FAILURE);
	}
}

static int	parse_file(int fd, t_map *map, int *flag, bool	start_end[])
{
	int		conf_last_line;
	char	*line;
	int		gnl_error;

	conf_last_line = 0;
	while (1)
	{
		line = get_next_line(fd, &gnl_error);
		if (gnl_error != 0)
			return (gnl_error_return(gnl_error));
		if (line == NULL)
			break ;
		if (!start_end[0])
			start_end[0] = check_if_map_started(*flag, line, &conf_last_line);
		if (*line == '\n' && !start_end[0])
		{
			free(line);
			continue ;
		}
		if (!start_end[0])
			validate_non_map_elements(line, flag, fd);
		else
			get_map_dimensions(line, map, start_end, fd);
	}
	return (conf_last_line + 1);
}

static void	check_missing_content(int map_start_line, \
				int config_flag, bool map_started, t_map *map)
{
	bool	config_missing;

	if (map_start_line == 1)
		put_error_and_exit("Empty file\n");
	config_missing = check_if_config_missing(config_flag);
	if (config_missing || !map_started || map->width == 0)
		ft_putstr_fd("Error\n", 2);
	if (config_missing)
	{
		ft_putstr_fd("Missing config:\n", 2);
		print_missing_config(config_flag);
	}
	if (!map_started || map->width == 0)
		ft_putstr_fd("Missing map\n", 2);
	if (config_missing || !map_started || map->width == 0)
		exit(EXIT_FAILURE);
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
	int		config_flag;
	bool	map_start_end[2];
	int		map_start_line;
	char	**grid;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_and_exit("open() error");
	map->width = 0;
	map->height = 0;
	config_flag = 0;
	ft_bzero(map_start_end, sizeof(bool) * 2);
	map_start_line = parse_file(fd, map, &config_flag, map_start_end);
	if (close(fd) == -1)
		perror_and_exit("close() error");
	if (map_start_line == -1)
		exit (1);
	check_missing_content(map_start_line, config_flag, map_start_end[0], map);
	grid = init_char_grid(file, map, map_start_line);
	if (PRINT_MAP_AND_MINIMAP)
		print_char_grid(grid, map);
	validate_map(grid, map);
	free_char_grid(grid);
}

void	validate_input(int argc, char **argv, t_map *map)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Invalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ./cub3D path_to_file.cub\n", 1);
		exit(EXIT_FAILURE);
	}
	validate_file_extension(argv[1]);
	validate_file_content(argv[1], map);
}
