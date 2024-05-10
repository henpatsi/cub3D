/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:59:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/10 13:50:20 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	movement_hook(void *param)
{
	t_map	*map;
	int		forward_input;
	int		right_input;
	double	rotate_amount;

	map = (t_map *) param;
	forward_input = 0;
	right_input = 0;
	rotate_amount = 0.0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		forward_input += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		forward_input -= 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		right_input += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		right_input -= 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		rotate_amount += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		rotate_amount -= 1;
	move_player(map, forward_input, right_input);
	rotate_player(map, rotate_amount);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *) param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		map->animation.active = 1;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
}

void	cursor_input_hook(double xpos, double ypos, void *param)
{
	t_map	*map;

	map = (t_map *) param;
	(void) ypos;
	rotate_player(map, (xpos - map->mlx->width / 2) * MOUSE_SENSITIVITY);
	mlx_set_mouse_pos(map->mlx, map->mlx->width / 2, map->mlx->height / 2);
}

void	update_visuals_hook(void *param)
{
	t_map			*map;
	static t_vector	old_pos;
	static double	old_rot;

	map = (t_map *) param;
	if (map->player.x == old_pos.x && map->player.y == old_pos.y
		&& map->player.x_rotation == old_rot)
		return ;
	update_visuals(map);
	reload_and_draw_minimap(map, map->canvas);
	old_pos.x = map->player.x;
	old_pos.y = map->player.y;
	old_rot = map->player.x_rotation;
}

void	animation_hook(void *param)
{
	t_map	*map;

	map = (t_map *) param;
	update_animation(map->mlx, &map->animation);
}
