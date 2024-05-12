/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:40:14 by ixu               #+#    #+#             */
/*   Updated: 2024/05/12 22:56:48 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_identifiers(char **split_line, char *line, int *config_flag)
{
	int					i;
	bool				is_identifier;
	const char			*identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	const t_config_flag	flags[6] = {NO_FLAG, SO_FLAG, WE_FLAG, EA_FLAG, \
									F_FLAG, C_FLAG};

	i = -1;
	is_identifier = false;
	while (++i < 6)
	{
		if (ft_strcmp(split_line[0], identifiers[i]) == 0)
		{
			is_identifier = true;
			if ((*config_flag & flags[i]) == 0)
				*config_flag |= flags[i];
			else
				non_map_error("Duplicate type identifier in the line:\n", \
					line, split_line);
			break ;
		}
	}
	if (!is_identifier)
		non_map_error("Invalid type identifier in the line:\n", \
						line, split_line);
}

bool	check_if_line_contains_map_content(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (ft_strchr(" 1", line[i]) == NULL)
			return (false);
		i++;
	}
	return (true);
}

void	validate_non_map_elements(char *line, int *config_flag)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
	{
		ft_putendl_fd("malloc() error", 2);
		free(line);
		exit(EXIT_FAILURE);
	}
	if (check_if_line_contains_map_content(line))
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Missing config:\n", 2);
		print_missing_config(*config_flag);
		exit(EXIT_FAILURE);
	}
	if (split_line[0] == NULL || split_line[1] == NULL || split_line[2] != NULL)
		non_map_error("Invalid number of arguments in the line:\n", \
						line, split_line);
	check_identifiers(split_line, line, config_flag);
	ft_freestrs(split_line);
}

bool	check_if_config_missing(int config_flag)
{
	int					i;
	const t_config_flag	flags[6] = {NO_FLAG, SO_FLAG, WE_FLAG, \
										EA_FLAG, F_FLAG, C_FLAG};

	i = -1;
	while (++i < 6)
	{
		if ((config_flag & flags[i]) == 0)
			return (true);
	}
	return (false);
}

bool	check_if_map_started(int config_flag, char *line)
{
	if (check_if_config_missing(config_flag))
		return (false);
	if (check_if_line_contains_map_content(line))
		return (true);
	return (false);
}

void	get_map_dimensions(char *line, t_map *map)
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
