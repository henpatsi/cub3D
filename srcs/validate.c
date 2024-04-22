/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:27:31 by ixu               #+#    #+#             */
/*   Updated: 2024/04/22 16:14:28 by ixu              ###   ########.fr       */
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

static void validate_file_content(char *file, t_map *map)
{
	int		fd;
	char	*line;
	char	**info;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	int	i = 1; // to be removed
	while (line != NULL)
	{
		printf("line %3d: %s", i, line); // to be removed
		i++; // to be removed
		if (*line == '\0') // white spaces?
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		info = ft_split(line, ' ');
		if (info == NULL) // in what cases null is returned
		{
			ft_putendl_fd("malloc() error", 2);
			free(line);
			exit(EXIT_FAILURE);
		}
		// validate_element();
		free_arr(info);
		free(line);
		line = get_next_line(fd);
	}
	(void)map;
	if (close(fd) == -1)
	{
		perror("Error");
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
