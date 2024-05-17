/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:14:34 by ixu               #+#    #+#             */
/*   Updated: 2024/05/17 13:35:34 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_player(t_map *map, int y, int x)
{
	if ((int)map->player.y == y && (int)map->player.x == x)
		return (true);
	return (false);
}

static bool	player_next_to_door(t_map *map, t_gridpos door_gridpos)
{
	double	player_x;
	double	player_y;

	player_x = map->player.x;
	player_y = map->player.y;
	if ((is_player(map, door_gridpos.y + 1, door_gridpos.x)
			&& player_y - PLAYER_SIZE >= door_gridpos.y + 1 - EPSILON)
		|| (is_player(map, door_gridpos.y - 1, door_gridpos.x)
			&& player_y + PLAYER_SIZE <= door_gridpos.y + EPSILON)
		|| (is_player(map, door_gridpos.y, door_gridpos.x + 1)
			&& player_x - PLAYER_SIZE >= door_gridpos.x + 1 - EPSILON)
		|| (is_player(map, door_gridpos.y, door_gridpos.x - 1)
			&& player_x + PLAYER_SIZE <= door_gridpos.x + EPSILON))
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

void	handle_door_actions(t_map *map)
{
	t_vector	origin;
	t_hitinfo	hit;
	t_gridpos	door_gridpos;

	ft_bzero(&hit, sizeof(t_hitinfo));
	origin.x = map->player.x;
	origin.y = map->player.y;
	grid_raycast(&hit, map, origin, map->player.dir);
	if ((hit.tile_info.type == CLOSED_DOOR && hit.distance < 1)
		|| hit.hit_open_door)
	{
		if (hit.hit_open_door)
			door_gridpos = hit.open_door_info;
		else
			door_gridpos = hit.tile_info;
		if (player_next_to_door(map, door_gridpos))
		{
			toggle_door_state(map, door_gridpos.y, door_gridpos.x);
			update_visuals(map);
			update_minimap(map);
		}
	}
}
