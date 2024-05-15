/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:55:22 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/15 15:00:42 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (1);
}
