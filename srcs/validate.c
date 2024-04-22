/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:27:31 by ixu               #+#    #+#             */
/*   Updated: 2024/04/22 23:27:05 by ixu              ###   ########.fr       */
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

static void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
}

static void	handle_error(char *line, char **split_line)
{
	ft_putstr_fd("Error\nInvalid element: ", 2);
	ft_putstr_fd(line, 2);
	free(line);
	free_arr(split_line);
	exit(EXIT_FAILURE);
}

static void	validate_element(char *line, int *flags)
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
		handle_error(line, split_line);
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
				handle_error(line, split_line);
			break ;
		}
	}
	if (!is_identifier)
		handle_error(line, split_line);
	free_arr(split_line);
}

static void validate_file_content(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		flags;

	(void)map; // to be removed
	// int	i = 1; // to be removed
	flags = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open() error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = get_next_line(fd); // malloc, read error?
		if (line == NULL)
			break ;
		// printf("line %3d: %s", i++, line); // to be removed
		if (*line == '\n') // white spaces?
		{
			free(line);
			continue ;
		}
		validate_element(line, &flags); // validate texture path during data init with mlx_load_png()? 
		// validate_map(line);
		free(line);
	}
	if (close(fd) == -1)
	{
		perror("close() error");
		exit(EXIT_FAILURE);
	}
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
