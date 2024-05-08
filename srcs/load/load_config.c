/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:56:33 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/08 14:15:52 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_valid_color(char **color_split)
{
	int	r;
	int	g;
	int	b;

	if (color_split[0] == 0 || color_split[1] == 0 || color_split[2] == 0)
		return (return_error("Color config rgb incomplete"));
	if (color_split[3] != 0)
		return (return_error("Color config rgb has extra values"));
	r = ft_atoi(color_split[0]);
	if (r < 0 || r > 255)
		return (return_error("rgb values must be between 0 and 255"));
	g = ft_atoi(color_split[1]);
	if (g < 0 || g > 255)
		return (return_error("rgb values must be between 0 and 255"));
	b = ft_atoi(color_split[2]);
	if (b < 0 || b > 255)
		return (return_error("rgb values must be between 0 and 255"));
	return (1);
}

int	init_color(t_map *map, char **split_line)
{
	uint32_t	color;
	char		**color_split;

	if (split_line[1] == 0)
		return (return_error("Color config missing rgb"));
	split_line[1][ft_strlen(split_line[1]) - 1] = 0;
	color_split = ft_split(split_line[1], ',');
	if (color_split == 0)
		return (return_error("Failed to read color config"));
	if (check_valid_color(color_split) == -1)
	{
		free_strs(color_split);
		return (-1);
	}
	color = ft_atoi(color_split[0]);
	color = (color << 8) + ft_atoi(color_split[1]);
	color = (color << 8) + ft_atoi(color_split[2]);
	color = (color << 8) + 255;
	if (ft_strcmp(split_line[0], "F") == 0)
		map->floor_color = color;
	if (ft_strcmp(split_line[0], "C") == 0)
		map->ceiling_color = color;
	free_strs(color_split);
	return (1);
}

int	init_wall_texture(t_map *map, char **split_line)
{
	mlx_texture_t	*texture;

	if (split_line[1] == 0)
		return (return_error("Failed to read texture config"));
	split_line[1][ft_strlen(split_line[1]) - 1] = 0;
	texture = mlx_load_png(split_line[1]);
	if (texture == 0)
		return (-1);
	if (ft_strcmp(split_line[0], "NO") == 0)
		map->textures.north = texture;
	if (ft_strcmp(split_line[0], "SO") == 0)
		map->textures.south = texture;
	if (ft_strcmp(split_line[0], "WE") == 0)
		map->textures.west = texture;
	if (ft_strcmp(split_line[0], "EA") == 0)
		map->textures.east = texture;
	return (1);
}

char	**read_split_line(int map_fd)
{
	char	*line;
	char	**split_line;

	line = get_next_line(map_fd);
	if (line == 0)
		return (0);
	split_line = ft_split(line, ' ');
	free(line);
	if (split_line[0] == 0)
	{
		free_strs(split_line);
		return (0);
	}
	return (split_line);
}

int	load_config(t_map *map, int map_fd)
{
	int		config_count;
	char	**split;
	int		ret;

	config_count = 0;
	while (config_count < 6)
	{
		split = read_split_line(map_fd);
		if (split == 0)
		{
			free_textures(map->textures);
			return (return_error("Failed to read config"));
		}
		if (ft_strcmp(split[0], "\n") == 0)
		{
			free_strs(split);
			continue ;
		}
		if (ft_strcmp(split[0], "F") == 0 || ft_strcmp(split[0], "C") == 0)
			ret = init_color(map, split);
		else
			ret = init_wall_texture(map, split);
		free_strs(split);
		if (ret == -1)
		{
			free_textures(map->textures);
			return (-1);
		}
		config_count++;
	}
	return (1);
}
