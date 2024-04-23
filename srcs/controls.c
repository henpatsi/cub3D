/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:45:59 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/23 10:18:36 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_map *map, int x, int y)
{
	map->player.x += x * map->mlx->delta_time * MOVE_SPEED;
	map->player.y += y * map->mlx->delta_time * MOVE_SPEED;
	printf("\nplayer x: %f, y: %f, rot: %f\n\n", map->player.x, map->player.y, map->player.x_rotation);
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
		move_player(map, -1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		move_player(map, 1, 0);

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
}