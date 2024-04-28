/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/28 18:35:35 by ixu              ###   ########.fr       */
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
	map->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", false);
	if (map->mlx == 0)
	{
		ft_putstr_fd("Failed to init mlx\n", 2);
		return (1);
	}
	// --- for testing minimap ---
	map->images.initial = mlx_new_image(map->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (map->images.initial == NULL)
	{
		mlx_close_window(map->mlx);
		ft_putstr_fd("Failed to create image\n", 2);
		return (1);
	}
	if (mlx_image_to_window(map->mlx, map->images.initial, 0, 0) == -1)
	{
		mlx_close_window(map->mlx);
		ft_putstr_fd("Failed to draw image onto the window\n", 2);
		return (1);
	}

	if (load_map(map, argv[1]) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}

	print_grid(map);

	if (create_minimap_grid(map, map->minimap) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	if (create_minimap_pixel_grid(map->minimap) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	draw_minimap(map, map->images.initial);

	mlx_key_hook(map->mlx, key_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);

	free_mini_grid(map->minimap->grid);
	free_mini_grid(map->minimap->pixel_grid);

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
