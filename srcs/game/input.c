/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:59:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/04 15:39:16 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	keyboard_input_hook(void *param)
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
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	update_visuals(map);
	reload_and_draw_minimap(map, map->images.draw);
}

void	cursor_input_hook(double xpos, double ypos, void *param)
{
	t_map			*map;
	static double	last_xpos;
	
	(void) ypos;
	map = (t_map *) param;
	rotate_player(map, (double)(xpos - last_xpos) * MOUSE_SENSITIVITY);
	update_visuals(map);
	last_xpos = xpos;
}