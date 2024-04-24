/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:09 by ixu               #+#    #+#             */
/*   Updated: 2024/04/24 12:12:59 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_closed(int r, int c, t_map *map, char **grid)
{
	if (r < 0 || r >= map->height || c < 0 || c >= map->width)
		return (false);
	if (grid[r][c] == ' ')
		return (false);
	return (true);	
}

static void	validate_walls(char **grid, t_map *map)
{
	int	r;
	int	c;

	r = 0;
	while (r < map->height)
	{
		c = 0;
		while (c < map->width)
		{
			if (grid[r][c] == '0')
			{
				if (!is_closed(r + 1, c, map, grid))
					map_error("Map not closed by walls\n", grid, map);
				if (!is_closed(r - 1, c, map, grid))
					map_error("Map not closed by walls\n", grid, map);
				if (!is_closed(r, c + 1, map, grid))
					map_error("Map not closed by walls\n", grid, map);
				if (!is_closed(r, c - 1, map, grid))
					map_error("Map not closed by walls\n", grid, map);
			}
			c++;
		}
		r++;
	}
}

void	validate_map(char **grid, t_map *map)
{
	int		row;
	int		col;
	bool	player_found;

	row = 0;
	player_found = false;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (ft_strchr("01NSEW ", grid[row][col]) == NULL)
				map_error("Map contains an invalid character\n", grid, map);
			if (ft_strchr("NSEW", grid[row][col]) != NULL && !player_found)
				player_found = true;
			else if (ft_strchr("NSEW", grid[row][col]) != NULL && player_found)
				map_error("Map contains more than one start position\n", grid, map);
			col++;
		}
		row++;
	}
	if (!player_found)
		map_error("Map missing start position\n", grid, map);
	validate_walls(grid, map);
}

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
		// if (line[col] == ' ')
		// 	grid[row][col] = '0';
		// else
		grid[row][col] = line[col];
		col++;
	}
	while (col < map->width)
	{
		grid[row][col] = ' ';
		col++;
	}
}

char	**grid_init(char *file, t_map *map)
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
	printf("map width: %d\n", map->width);
	printf("map height: %d\n", map->height);
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
