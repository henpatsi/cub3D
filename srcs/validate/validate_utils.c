/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:40:14 by ixu               #+#    #+#             */
/*   Updated: 2024/05/12 17:30:19 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_identifiers(char **split_line, char *line, int *flags)
{
	int				i;
	bool			is_identifier;
	const char		*identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	const t_flags	flag_values[6] = {NO_FLAG, SO_FLAG, WE_FLAG, EA_FLAG, \
										F_FLAG, C_FLAG};

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
}

void	validate_non_map_elements(char *line, int *flags)
{
	char			**split_line;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
	{
		ft_putendl_fd("malloc() error", 2);
		free(line);
		exit(EXIT_FAILURE);
	}
	if (split_line[0] == NULL || split_line[1] == NULL || split_line[2] != NULL)
		non_map_error(line, split_line);
	check_identifiers(split_line, line, flags);
	ft_freestrs(split_line);
}

bool	map_started(int flags)
{
	int				i;
	const t_flags	flag_values[6] = {NO_FLAG, SO_FLAG, WE_FLAG, \
										EA_FLAG, F_FLAG, C_FLAG};

	i = -1;
	while (++i < 6)
	{
		if ((flags & flag_values[i]) == 0)
			return (false);
	}
	return (true);
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
