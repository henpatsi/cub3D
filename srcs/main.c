/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/24 10:17:00 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_grid(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x].type == EMPTY)
				ft_printf("0");
			else
				ft_printf("1");
			x++;
		}
		ft_printf("\n");
		y++;
	}

	printf("\nplayer x: %f, y: %f, rot: %f\n\n", map->player.x, map->player.y, map->player.x_rotation);
}

int test_game(t_map *map, char **argv)
{
	map->width = 6;
	map->height = 6;

	map->mlx = mlx_init(512, 512, "cub3D", false);
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

	mlx_key_hook(map->mlx, key_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);

	return (1);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		ft_putstr_fd("Use: ./cub3D path_to_map\n", 2);
		return (1);
	}

	test_game(&map, argv);

	return (0);
}
