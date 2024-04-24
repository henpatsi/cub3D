/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:27:31 by ixu               #+#    #+#             */
/*   Updated: 2024/04/24 08:39:57 by ixu              ###   ########.fr       */
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

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	non_map_error(char *line, char **split_line)
{
	ft_putstr_fd("Error\nInvalid element: ", 2);
	ft_putstr_fd(line, 2);
	free(line);
	free_arr(split_line);
	exit(EXIT_FAILURE);
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

// static void	safe_close(void)
// {
// 	perror("close() error");
// 	exit(EXIT_FAILURE);
// }

static void	fill_in_grid(char *line, t_map *map, char **grid, int row)
{
	int	col;

	col = 0;
	grid[row] = (char *)malloc(sizeof(char) * map->width);
	if (grid[row] == NULL)
	{
		// free_prev_allocated
		free(line);
		// close();
		exit(EXIT_FAILURE);
	}
	while (col < map->width && (line[col] != '\n' && line[col] != '\0'))
	{
		if (line[col] == ' ')
			grid[row][col] = '0';
		else
			grid[row][col] = line[col];
		col++;
	}
	while (col < map->width)
	{
		grid[row][col] = '0';
		col++;
	}
}

static char	**grid_init(char *file, t_map *map)
{
	char	**grid;
	int		row;
	int		fd;
	char	*line;

	row = 0;
	grid = (char **)malloc(sizeof(char *) * map->height);
	if (grid == NULL)
	{
		ft_putstr_fd("malloc() error\n", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open() error");
		free(grid);
		exit(EXIT_FAILURE);
	}
	// int	i = 1;
	while (1)
	{
		line = get_next_line(fd); // malloc, read error?
		if (line == NULL)
			break ;
		// printf("line %3d: %s", i++, line);
		if (*line == '\n' || *line == 'N' || *line == 'S' || *line == 'W' || *line == 'E' || *line == 'F' || *line == 'C')
		{
			free(line);
			continue ;
		}
		fill_in_grid(line, map, grid, row);
		row++;
		free(line);
	}	
	if (close(fd) == -1)
	{
		perror("close() error");
		exit(EXIT_FAILURE);
	}
	// print grid
	for (int r = 0; r < map->height; r++)
	{
		for (int c = 0; c < map->width; c++)
		{
			if (grid[r][c] == '0')
				printf("%c", '.');
			else
				printf("%c", grid[r][c]);
		}
		printf("\n");
	}
	return (grid);
}

static void	free_grid(char **grid, t_map *map)
{
	int	row;

	row = 0;
	while (row < map->height)
	{
		free(grid[row]);
		row++;
	}
	free(grid);
}

static void	map_error(char *message, char **grid, t_map *map)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	free_grid(grid, map);
	exit(EXIT_FAILURE);
}
int	visited[15][36] = {0}; // malloc
static int	is_closed(int r, int c, t_map *map, char **grid) 
{
	int	closed;

	if (r < 0 || r >= map->height || c < 0 || c >= map->width)
		return (0);
	if (grid[r][c] == '1' || visited[r][c] == 1)
		return (1);
	visited[r][c] = 1;
	closed = is_closed(r + 1, c, map, grid) &
				is_closed(r - 1, c, map, grid) &
				is_closed(r, c + 1, map, grid) &
				is_closed(r, c - 1, map, grid);
	return (closed);
}

static void	validate_map(char **grid, t_map *map)
{
	int		row;
	int		col;
	bool	player_found;
	int		start_r;
	int		start_c;

	row = 0;
	player_found = false;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (ft_strchr("01NSEW", grid[row][col]) == NULL)
				map_error("Map contains an invalid character\n", grid, map);
			if (ft_strchr("NSEW", grid[row][col]) != NULL && !player_found)
			{
				player_found = true;
				start_r = row;
				start_c = col;
			}
			else if (ft_strchr("NSEW", grid[row][col]) != NULL && player_found)
				map_error("Map contains more than one start position\n", grid, map);
			col++;
		}
		row++;
	}
	// validate walls
	int	closed;
	closed = is_closed(start_r, start_c, map, grid);
	printf("is closed: %d\n", closed);
	if (!closed)
		map_error("Map not closed by walls\n", grid, map);
}

static void validate_file_content(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		flags;

	map->width = 0;
	map->height = 0;
	// int	i = 1;
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
	printf("\nmap width: %d\n", map->width);
	printf("map height: %d\n", map->height);
	if (close(fd) == -1)
	{
		perror("close() error");
		exit(EXIT_FAILURE);
	}
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
