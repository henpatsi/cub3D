/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:40:14 by ixu               #+#    #+#             */
/*   Updated: 2024/05/16 10:30:00 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_missing_config(int config_flag)
{
	if ((config_flag & NO_FLAG) == 0)
		ft_printf("- North texture\n");
	if ((config_flag & SO_FLAG) == 0)
		ft_printf("- South texture\n");
	if ((config_flag & WE_FLAG) == 0)
		ft_printf("- West texture\n");
	if ((config_flag & EA_FLAG) == 0)
		ft_printf("- East texture\n");
	if ((config_flag & F_FLAG) == 0)
		ft_printf("- Floor color\n");
	if ((config_flag & C_FLAG) == 0)
		ft_printf("- Ceiling color\n");
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

bool	check_if_line_contains_map_content(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n' || line[i] == '\0')
		return (false);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (ft_strchr(" 1", line[i]) == NULL)
			return (false);
		i++;
	}
	return (true);
}

bool	check_if_map_started(int config_flag, char *line, int *conf_last_line)
{
	if (check_if_config_missing(config_flag))
	{
		*conf_last_line += 1;
		return (false);
	}
	if (check_if_line_contains_map_content(line))
		return (true);
	*conf_last_line += 1;
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
	free(line);
}
