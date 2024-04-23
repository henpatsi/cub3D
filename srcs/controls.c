/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:45:59 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/24 10:07:47 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_map *map, int forward, int right)
{
	t_vector	target_pos;

	target_pos.x = map->player.x
		+ (forward * map->mlx->delta_time * MOVE_SPEED * map->player.dir.x)
		+ (right * map->mlx->delta_time * MOVE_SPEED * -map->player.dir.y);
	target_pos.y = map->player.y
		+ (forward * map->mlx->delta_time * MOVE_SPEED * map->player.dir.y)
		+ (right * map->mlx->delta_time * MOVE_SPEED * map->player.dir.x);
	if (target_pos.x < 0 || target_pos.x >= map->width)
		return ;
	if (target_pos.y < 0 || target_pos.y >= map->height)
		return ;
	if (map->grid[(int) target_pos.y][(int) target_pos.x].type == WALL)
		return ;
	map->player.x = target_pos.x;
	map->player.y = target_pos.y;
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

	update_visuals(map);

	printf("\nplayer x: %f, y: %f, rot: %f\n", map->player.x, map->player.y, map->player.x_rotation);
	printf("player vec x: %f, vec y: %f\n\n", map->player.dir.x, map->player.dir.y);
}
