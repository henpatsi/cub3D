/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:45:59 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/30 14:25:21 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	get_target_position(t_map *map, int forward, int right)
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

t_vector	limit_target_to_walls(t_map *map, t_vector target_pos)
{
	t_hitinfo	hit;
	t_vector	origin;
	t_vector	dir;

	origin.x = map->player.x;
	origin.y = map->player.y;
	dir.x = target_pos.x - origin.x;
	dir.y = 0;
	if (dir.x != 0 && grid_raycast(&hit, map, origin, dir) == 1)
	{
		if ((dir.x > 0 && hit.x < target_pos.x)
			|| (dir.x < 0 && hit.x > target_pos.x))
			target_pos.x = hit.x;
	}
	dir.x = 0;
	dir.y = target_pos.y - origin.y;
	if (dir.y != 0 && grid_raycast(&hit, map, origin, dir) == 1)
	{
		if ((dir.y > 0 && hit.y < target_pos.y)
			|| (dir.y < 0 && hit.y > target_pos.y))
			target_pos.y = hit.y;
	}
	return (target_pos);
}

void	move_player(t_map *map, int forward, int right)
{
	t_vector	target_pos;

	target_pos = get_target_position(map, forward, right);
	if (target_pos.x < 0 || target_pos.x >= map->width
		|| target_pos.y < 0 || target_pos.y >= map->height)
		return ;
	target_pos = limit_target_to_walls(map, target_pos);

	// Moce player to target position
	if (map->grid[(int) map->player.y][(int) target_pos.x].type != WALL)
		map->player.x = target_pos.x;
	if (map->grid[(int) target_pos.y][(int) map->player.x].type != WALL)
		map->player.y = target_pos.y;

	// Limit distance to wall to at least player size
	if (map->grid[(int) map->player.y][(int)(map->player.x + PLAYER_SIZE)].type == WALL)
		map->player.x = (int)(map->player.x + PLAYER_SIZE) - PLAYER_SIZE;
	else if (map->grid[(int) map->player.y][(int)(map->player.x - PLAYER_SIZE)].type == WALL)
		map->player.x = (int) map->player.x + PLAYER_SIZE;
	if (map->grid[(int)(map->player.y + PLAYER_SIZE)][(int) map->player.x].type == WALL)
		map->player.y = (int)(map->player.y + PLAYER_SIZE) - PLAYER_SIZE;
	else if (map->grid[(int)(map->player.y - PLAYER_SIZE)][(int) map->player.x].type == WALL)
		map->player.y = (int) map->player.y + PLAYER_SIZE;
}

void	rotate_player(t_map *map, int dir)
{
	double	rotation;
	double	rotation_rad;

	rotation = map->player.x_rotation
		+ (dir * map->mlx->delta_time * ROTATE_SPEED);
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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *) param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		move_player(map, 1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		move_player(map, -1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		move_player(map, 0, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		move_player(map, 0, -1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		rotate_player(map, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		rotate_player(map, -1);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	printf("\nplayer x: %f, y: %f, rot: %f\n", map->player.x, map->player.y, map->player.x_rotation);
	printf("player vec x: %f, vec y: %f\n\n", map->player.dir.x, map->player.dir.y);
	update_visuals(map);
	reload_and_draw_minimap(map, map->images.draw);
}
