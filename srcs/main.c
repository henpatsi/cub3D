/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/27 16:44:59 by ixu              ###   ########.fr       */
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

void	print_minimap(t_minimap *minimap, bool scaled_up)
{
	int	y;
	int	x;

	if (!scaled_up)
		ft_printf("Original minimap length: %d\n", minimap->len);
	else
		ft_printf("Enlarged minimap length: %d\n", minimap->len);
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
	ft_printf("\n");
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
		print_minimap(minimap, false);
	return (0);
}

void	update_minimap(t_minimap *minimap, t_mini_gridpos **bigger_grid)
{
	int	my;
	int	mx;
	int	py;
	int	px;

	my = -1;
	while (++my < minimap->len)
	{
		mx = -1;
		while (++mx < minimap->len)
		{
			py = my * SCALE - 1;
			while (++py < (my + 1) * SCALE)
			{
				px = mx * SCALE - 1;
				while (++px < (mx + 1) * SCALE)
					bigger_grid[py][px].type = minimap->grid[my][mx].type;
			}
		}
	}
	free_mini_grid(minimap->grid);
	minimap->len *= SCALE;
	minimap->grid = bigger_grid;
	minimap->grid[APO * SCALE][APO * SCALE].type = PLAYER;
}

int	scale_up_minimap(t_minimap *minimap)
{
	t_mini_gridpos	**bigger_grid;
	int				new_len;
	int				y;

	new_len = minimap->len * SCALE;
	bigger_grid = ft_calloc(new_len + 1, sizeof(t_mini_gridpos *));
	if (bigger_grid == NULL)
		return (return_error("malloc() error"));
	y = -1;
	while (++y < new_len)
	{
		bigger_grid[y] = ft_calloc(new_len + 1, sizeof(t_mini_gridpos));
		if (bigger_grid[y] == NULL)
		{
			free_mini_grid(bigger_grid);
			return (return_error("malloc() error"));
		}
	}
	update_minimap(minimap, bigger_grid);
	if (DEBUG_MODE)
		print_minimap(minimap, true);
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
			mlx_put_pixel(image, x, y, 0x000000ff);
			// if (minimap->grid[y][x].type == EMPTY)
			// 	mlx_put_pixel(image, x, y, 0x000000ff);
			// else if (minimap->grid[y][x].type == WALL)
			// 	mlx_put_pixel(image, x, y, 0x000000ff); //diff color
			// else if (minimap->grid[y][x].type == PLAYER)
			// 	mlx_put_pixel(image, x, y, 0x000000ff); //diff color
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
	// scale up and pad
	if (scale_up_minimap(&minimap) == -1)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	// after the game is drawn
	draw_minimap(&minimap, image);

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
