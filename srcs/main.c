/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/30 10:12:04 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_grid(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x].type == EMPTY)
				ft_printf(".");
			else
				ft_printf("1");
			x++;
		}
		ft_printf("\n");
		y++;
	}
	printf("\nplayer x: %f, y: %f, rot: %f\n", map->player.x, map->player.y, map->player.x_rotation);
	printf("player dirx: %f, diry: %f, planex: %f planey: %f\n\n", map->player.dir.x, map->player.dir.y, map->player.cam_plane.x, map->player.cam_plane.y);
}

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
	print_grid(map);
	if (init_visuals(map) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	if (create_minimap_grid(map, &map->minimap) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	if (create_minimap_pixel_grid(&map->minimap) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	draw_minimap(map, map->images.draw);
	mlx_key_hook(map->mlx, key_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	free_grid(map->minimap.grid);
	free_grid(map->minimap.pixel_grid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;

	validate_input(argc, argv, &map);
	// printf("map width: %d\n", map.width);
	// printf("map height: %d\n", map.height);
	if (test_game(&map, argv))
		return (1);
	return (0);
}
