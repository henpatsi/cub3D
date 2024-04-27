/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/27 14:49:40 by ixu              ###   ########.fr       */
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

void	print_minimap(t_minimap *minimap)
{
	int	y;
	int	x;

	ft_printf("minimap length: %d\n", minimap->len);
	ft_printf("minimap apothem: %d\n\n", APO);
	y = -1;
	while (++y < minimap->len)
	{
		x = -1;
		while (++x < minimap->len)
		{
			if (minimap->grid[y][x].type == WALL)
				ft_printf("%c", '#');
			else if (minimap->grid[y][x].type == EMPTY)
				ft_printf("%c", '.');
			else if (minimap->grid[y][x].type == PLAYER)
				ft_printf("%c", 'P');
		}
		ft_printf("\n");
	}
}

void	init_minimap(t_map *map, t_minimap *minimap)
{
	int	y;
	int	x;
	int	mini_y;
	int	mini_x;

	minimap->player = map->player;
	y = map->player.y - APO;
	mini_y = 0;
	// printf("y min: %f\n", map->player.y - APO);
	// printf("y max: %f\n", map->player.y + APO);
	// printf("x min: %f\n", map->player.x - APO);
	// printf("x max: %f\n", map->player.x + APO);
	while (y >= map->player.y - APO && y <= map->player.y + APO)
	{
		x = map->player.x - APO;
		mini_x = 0;
		if (y >= 0 && y < map->height)
		{
			while (x >= map->player.x - APO && x <= map->player.x + APO)
			{
				if (x >= 0 && x < map->width)
					minimap->grid[mini_y][mini_x].type = map->grid[y][x].type;
				// printf("map->grid[y][x].type:%d\n", map->grid[y][x].type);
				x++;
				mini_x++;
			}
		}
		y++;
		mini_y++;
	}
	minimap->grid[APO][APO].type = PLAYER;
}

int	load_minimap(t_map *map, t_minimap *minimap)
{
	int	y;

	minimap->len = APO * 2 + 1;
	minimap->grid = ft_calloc(minimap->len + 1, sizeof(t_mini_gridpos *));
	if (minimap->grid == NULL)
		return (return_error("malloc() error"));
	y = -1;
	while (++y < minimap->len)
	{
		minimap->grid[y] = ft_calloc(minimap->len + 1, sizeof(t_mini_gridpos));
		if (minimap->grid[y] == NULL)
		{
			free_mini_grid(minimap->grid);
			return (return_error("malloc() error"));
		}
	}
	init_minimap(map, minimap);
	if (DEBUG_MODE)
		print_minimap(minimap);
	return (0);
}

void	draw_minimap(t_minimap *minimap, mlx_image_t *image)
{
	int	x;
	int	y;
	// int	minimap_height;
	// int	minimap_width;

	// minimap_height = IMG_HEIGHT * 0.25;
	// minimap_width = IMG_WIDTH * 0.25;
	y = -1;
	while (++y < minimap->len)
	{
		x = -1;
		while (++x < minimap->len)
		{
			if (minimap->grid[y][x].type == EMPTY)
				mlx_put_pixel(image, x, y, 0x000000ff);
			else if (minimap->grid[y][x].type == WALL)
				mlx_put_pixel(image, x, y, 0x000000ff); //diff color
			else if (minimap->grid[y][x].type == PLAYER)
				mlx_put_pixel(image, x, y, 0x000000ff); //diff color
		}
	}
}

int test_game(t_map *map, char **argv)
{
	mlx_image_t	*image;

	map->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", false);
	if (map->mlx == 0)
	{
		ft_putstr_fd("Failed to init mlx\n", 2);
		return (1);
	}
	// --- for testing minimap ---
	image = mlx_new_image(map->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (image == NULL)
	{
		mlx_close_window(map->mlx);
		ft_putstr_fd("Failed to create image\n", 2);
		return (1);
	}
	if (mlx_image_to_window(map->mlx, image, 0, 0) == -1)
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

	t_minimap	minimap;
	if (load_minimap(map, &minimap) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	(void)minimap;
	// scale up and pad
	// transform_minimap_to_screen();
	// after the game is drawn
	// draw_minimap(scaled_up_minimap, image);

	mlx_key_hook(map->mlx, key_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);

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
