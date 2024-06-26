/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:45:59 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/17 13:36:04 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_vector	get_target_position(t_map *map, double forward, double right)
{
	t_vector	target_pos;

	target_pos.x = map->player.x
		+ (forward * map->mlx->delta_time * MOVE_SPEED * map->player.dir.x)
		+ (right * map->mlx->delta_time * MOVE_SPEED * -map->player.dir.y);
	target_pos.y = map->player.y
		+ (forward * map->mlx->delta_time * MOVE_SPEED * map->player.dir.y)
		+ (right * map->mlx->delta_time * MOVE_SPEED * map->player.dir.x);
	return (target_pos);
}

static t_vector	limit_target_to_walls(t_map *map, t_vector target_pos)
{
	t_hitinfo	hit;
	t_vector	origin;
	t_vector	dir;

	ft_bzero(&hit, sizeof(t_hitinfo));
	origin.x = map->player.x;
	origin.y = map->player.y;
	dir.x = target_pos.x - origin.x;
	dir.y = target_pos.y - origin.y;
	grid_raycast(&hit, map, origin, dir);
	if (hit.tile_info.type == WALL || hit.tile_info.type == CLOSED_DOOR)
	{
		if (dir.x > 0 && hit.x < target_pos.x)
			target_pos.x = hit.x - 0.001;
		else if (dir.x < 0 && hit.x > target_pos.x)
			target_pos.x = hit.x + 0.001;
		if (dir.y > 0 && hit.y < target_pos.y)
			target_pos.y = hit.y - 0.001;
		else if (dir.y < 0 && hit.y > target_pos.y)
			target_pos.y = hit.y + 0.001;
	}
	return (target_pos);
}

static t_vector	apply_player_size(t_map *map, t_vector target_pos)
{
	if (map->grid[(int) target_pos.y]
		[(int)(target_pos.x + PLAYER_SIZE)].type == WALL
		|| map->grid[(int) target_pos.y]
		[(int)(target_pos.x + PLAYER_SIZE)].type == CLOSED_DOOR)
		target_pos.x = (int)(target_pos.x + PLAYER_SIZE) - PLAYER_SIZE;
	else if (map->grid[(int) target_pos.y]
		[(int)(target_pos.x - PLAYER_SIZE)].type == WALL
		|| map->grid[(int) target_pos.y]
		[(int)(target_pos.x - PLAYER_SIZE)].type == CLOSED_DOOR)
		target_pos.x = (int) target_pos.x + PLAYER_SIZE;
	if (map->grid[(int)(target_pos.y + PLAYER_SIZE)]
		[(int) target_pos.x].type == WALL
		|| map->grid[(int)(target_pos.y + PLAYER_SIZE)]
		[(int) target_pos.x].type == CLOSED_DOOR)
		target_pos.y = (int)(target_pos.y + PLAYER_SIZE) - PLAYER_SIZE;
	else if (map->grid[(int)(target_pos.y - PLAYER_SIZE)]
		[(int) target_pos.x].type == WALL
		|| map->grid[(int)(target_pos.y - PLAYER_SIZE)]
		[(int) target_pos.x].type == CLOSED_DOOR)
		target_pos.y = (int) target_pos.y + PLAYER_SIZE;
	return (target_pos);
}

void	move_player(t_map *map, double forward, double right)
{
	t_vector	target_pos;

	if (forward == 0 && right == 0)
		return ;
	target_pos = get_target_position(map, forward, right);
	if (target_pos.x < 0 || target_pos.x >= map->width
		|| target_pos.y < 0 || target_pos.y >= map->height)
		return ;
	target_pos = limit_target_to_walls(map, target_pos);
	target_pos = apply_player_size(map, target_pos);
	map->player.x = target_pos.x;
	map->player.y = target_pos.y;
}

void	rotate_player(t_map *map, double amount)
{
	double	rotation;
	double	rotation_rad;

	if (amount == 0)
		return ;
	rotation = map->player.x_rotation
		+ (amount * map->mlx->delta_time * ROTATE_SPEED);
	if (rotation > 360)
		rotation -= 360;
	if (rotation < 0)
		rotation += 360;
	map->player.x_rotation = rotation;
	rotation_rad = (rotation * PI) / 180;
	map->player.dir.x = sin(rotation_rad);
	map->player.dir.y = -cos(rotation_rad);
	map->player.cam_plane.x = cos(rotation_rad);
	map->player.cam_plane.y = sin(rotation_rad);
}
