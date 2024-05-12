/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/12 17:14:21 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	initialize_game(t_map *map)
{
	map->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", false);
	if (map->mlx == 0)
		return (-1);
	if (init_visuals(map) == -1)
		return (-1);
	if (init_minimap(map) == -1)
		return (-1);
	if (load_animations(map->mlx, &map->animation) == -1)
		return (-1);
	mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
	return (1);
}

int	run_game(t_map *map)
{
	mlx_cursor_hook(map->mlx, cursor_input_hook, map);
	mlx_key_hook(map->mlx, key_hook, map);
	if (!mlx_loop_hook(map->mlx, movement_hook, map))
		return (1);
	if (!mlx_loop_hook(map->mlx, update_visuals_hook, map))
		return (1);
	if (!mlx_loop_hook(map->mlx, animation_hook, map))
		return (1);
	mlx_loop(map->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		ret;

	ret = 0;
	ft_bzero(&map, sizeof(t_map));
	validate_input(argc, argv, &map);
	load_map(&map, argv[1]);
	if (initialize_game(&map) == -1)
	{
		mlx_terminate(map.mlx);
		return (1);
	}
	ret = run_game(&map);
	mlx_terminate(map.mlx);
	free_all(&map);
	return (ret);
}
