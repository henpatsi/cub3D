/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:14:34 by ixu               #+#    #+#             */
/*   Updated: 2024/05/09 12:23:47 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_door(t_map *map, int y, int x)
{
	if (map->grid[y][x].type == CLOSED_DOOR)
		return (true);
	if (map->grid[y][x].type == OPEN_DOOR)
		return (true);
	return (false);
}

static void	toggle_door_state(t_map *map, int y, int x)
{
	if (map->grid[y][x].type == CLOSED_DOOR)
		map->grid[y][x].type = OPEN_DOOR;
	else if (map->grid[y][x].type == OPEN_DOOR)
		map->grid[y][x].type = CLOSED_DOOR;
}

bool	next_to_door(t_map *map)
{
	int	x;
	int	y;

	x = (int)map->player.x;
	y = (int)map->player.y;
	if (is_door(map, y + 1, x))
		toggle_door_state(map, y + 1, x);
	else if (is_door(map, y - 1, x))
		toggle_door_state(map, y - 1, x);
	else if (is_door(map, y, x + 1))
		toggle_door_state(map, y, x + 1);
	else if (is_door(map, y, x - 1))
		toggle_door_state(map, y, x - 1);
	else
		return (false);
	return (true);
}
