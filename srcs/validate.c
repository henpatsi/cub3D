/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:27:31 by ixu               #+#    #+#             */
/*   Updated: 2024/04/24 12:42:29 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_file_extension(char *file)
{
	char	*filename;
	char	*extension;

	filename = ft_strdup(file);
	if (filename == NULL)
	{
		ft_putendl_fd("malloc() error", 2);
		exit(EXIT_FAILURE);
	}
	extension = ft_strdup(".cub");
	if (extension == NULL)
	{
		ft_putendl_fd("malloc() error", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(filename + ft_strlen(filename) - 4, extension) != 0)
	{
		free(filename);
		free(extension);
		ft_putendl_fd("Invalid file extension", 2);
		ft_putendl_fd("Usage: ./cub3D example.cub", 1);
		exit(EXIT_FAILURE);
	}
	free(filename);
	free(extension);
}

static void	validate_non_map_elements(char *line, int *flags)
{
	char			**split_line;
	int				i;
	bool			is_identifier;
	const char		*identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	const t_flags	flag_values[6] = {NO_FLAG, SO_FLAG, WE_FLAG, EA_FLAG, \
										F_FLAG, C_FLAG};

	split_line = ft_split(line, ' ');
	if (split_line == NULL) // in what cases null is returned
	{
		ft_putendl_fd("malloc() error", 2);
		free(line);
		exit(EXIT_FAILURE);
	}
	if (split_line[0] == NULL || split_line[1] == NULL || split_line[2] != NULL)
		non_map_error(line, split_line);
	i = -1;
	is_identifier = false;
	while (++i < 6)
	{
		if (ft_strcmp(split_line[0], identifiers[i]) == 0)
		{
			is_identifier = true;
			if ((*flags & flag_values[i]) == 0)
				*flags |= flag_values[i];
			else
				non_map_error(line, split_line);
			break ;
		}
	}
	if (!is_identifier)
		non_map_error(line, split_line);
	free_arr(split_line);
}

static bool	map_started(int flags)
{
	int				i;
	const t_flags	flag_values[6] = {NO_FLAG, SO_FLAG, WE_FLAG, EA_FLAG, \
										F_FLAG, C_FLAG};

	i = -1;
	while (++i < 6)
	{
		if ((flags & flag_values[i]) == 0)
			return (false);
	}
	return (true);
}

static void	get_map_dimensions(char *line, t_map *map)
{
	int	width;
	int	i;

	map->height++;
	width = 0;
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		width++;
		i++;
	}
	if (width > map->width)
		map->width = width;
}

static void	go_through_file(int fd, t_map *map)
{
	char	*line;
	int		flags;

	flags = 0;
	map->width = 0;
	map->height = 0;
	// int	i = 1;
	while (1)
	{
		line = get_next_line(fd); // malloc, read error?
		if (line == NULL)
			break ;
		// printf("line %3d: %s", i++, line);
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		// printf("map_started:%d\n", map_started(flags));
		if (!map_started(flags))
			validate_non_map_elements(line, &flags); // validate texture path during data init with mlx_load_png()? 
		else
			get_map_dimensions(line, map);
		free(line);
	}
}

static void	validate_file_content(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_and_exit("open() error");
	go_through_file(fd, map);
	if (close(fd) == -1)
		perror_and_exit("close() error");
	char	**grid;
	grid = grid_init(file, map);
	validate_map(grid, map);
	free_grid(grid, map);
}

void	validate_input(int argc, char **argv, t_map *map)
{
	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		ft_putendl_fd("Usage: ./cub3D example.cub", 1);
		exit(EXIT_FAILURE);
	}
	validate_file_extension(argv[1]);
	validate_file_content(argv[1], map);
}
