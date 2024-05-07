/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/07 14:18:54 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	test_game(t_map *map, char **argv)
{
	map->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", false);
	if (map->mlx == 0)
	{
		ft_putstr_fd("Failed to init mlx\n", 2);
		return (1);
	}
	if (load_map(map, argv[1]) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	if (init_visuals(map) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	if (init_minimap(map) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(map->mlx, cursor_input_hook, map);
	mlx_key_hook(map->mlx, key_hook, map);
	mlx_loop_hook(map->mlx, keyboard_input_hook, map);
	mlx_loop_hook(map->mlx, update_visuals_hook, map);
	mlx_loop_hook(map->mlx, animation_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	free_all(map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;

	validate_input(argc, argv, &map);
	if (test_game(&map, argv))
		return (1);
	return (0);
}
