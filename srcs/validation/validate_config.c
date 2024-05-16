/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:36:01 by ixu               #+#    #+#             */
/*   Updated: 2024/05/16 12:36:40 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_identifiers(char **split_line, char *line, int *config_flag,
				int fd)
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
					line, split_line, fd);
			break ;
		}
	}
	if (!is_identifier)
		non_map_error("Invalid type identifier in the line:\n", \
						line, split_line, fd);
}

void	validate_non_map_elements(char *line, int *config_flag, int fd)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
	{
		ft_putendl_fd("malloc() error", 2);
		free(line);
		close_file_and_exit(fd);
	}
	if (check_map_content(line))
	{
		ft_putstr_fd("Error\nMissing config:\n", 2);
		print_missing_config(*config_flag);
		free(line);
		ft_freestrs(split_line);
		close_file_and_exit(fd);
	}
	if (split_line[0] == NULL || split_line[1] == NULL
		|| (split_line[2] != NULL && *split_line[2] != '\n'))
		non_map_error("Invalid number of arguments in the line:\n", \
						line, split_line, fd);
	check_identifiers(split_line, line, config_flag, fd);
	ft_freestrs(split_line);
	free(line);
}
