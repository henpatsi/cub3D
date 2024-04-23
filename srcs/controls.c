/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:45:59 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/23 10:40:51 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_map *map, int x, int y)
{
	float target_pos[2];

	target_pos[0] = map->player.x + x * map->mlx->delta_time * MOVE_SPEED;
	target_pos[1] = map->player.y + y * map->mlx->delta_time * MOVE_SPEED;
	if (target_pos[0] < 0 || target_pos[0] >= map->width)
		return ;
	if (target_pos[1] < 0 || target_pos[1] >= map->height)
		return ;
	if (map->grid[(int) target_pos[1]][(int) target_pos[0]].type == WALL)
		return ;
	map->player.x = target_pos[0];
	map->player.y = target_pos[1];
}

void	rotate_player(t_map *map, int dir)
{
	map->player.x_rotation += dir * map->mlx->delta_time * ROTATE_SPEED;
	if (map->player.x_rotation > 360)
		map->player.x_rotation -= 360;
	if (map->player.x_rotation < 0)
		map->player.x_rotation += 360;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map *map;

	map = (t_map *) param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		move_player(map, 0, -1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		move_player(map, 0, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		move_player(map, 1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		move_player(map, -1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		rotate_player(map, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		rotate_player(map, -1);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);

	printf("\nplayer x: %f, y: %f, rot: %f\n\n", map->player.x, map->player.y, map->player.x_rotation);
}