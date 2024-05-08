/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:28:58 by ixu               #+#    #+#             */
/*   Updated: 2024/05/08 22:02:32 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_vectors(t_vector *vec_front_middle, \
	t_vector *vec_back_left, t_vector *vec_back_right, t_map *map)
{
	int		center;
	double	radius;
	double	rot;

	center = map->minimap.pixel_grid_len / 2 + PAD;
	radius = SCALE / 2;
	rot = map->player.x_rotation;
	vec_front_middle->x = center + radius * sin(deg_to_rad(rot));
	vec_front_middle->y = center - radius * cos(deg_to_rad(rot));
	vec_back_left->x = center - radius * sin(deg_to_rad(120 - rot));
	vec_back_left->y = center - radius * cos(deg_to_rad(120 - rot));
	vec_back_right->x = center + radius * cos(deg_to_rad(30 + rot));
	vec_back_right->y = center + radius * sin(deg_to_rad(30 + rot));
}

static void	draw_player(t_map *map)
{
	double		center;
	t_vector	vec_center;
	t_vector	vec_front_middle;
	t_vector	vec_back_left;
	t_vector	vec_back_right;

	center = map->minimap.pixel_grid_len / 2 + PAD;
	vec_center.x = center;
	vec_center.y = center;
	get_vectors(&vec_front_middle, &vec_back_left, &vec_back_right, map);
	draw_line(vec_front_middle, vec_back_left, map->canvas);
	draw_line(vec_back_left, vec_center, map->canvas);
	draw_line(vec_center, vec_back_right, map->canvas);
	draw_line(vec_back_right, vec_front_middle, map->canvas);
}

static bool	is_drawable(int x, int y, int move_x, int move_y)
{
	if (x >= move_x + 0.5 * SCALE && x <= D * SCALE * 2 + move_x + 0.5 * SCALE
		&& y >= move_y + 0.5 * SCALE
		&& y <= D * SCALE * 2 + move_y + 0.5 * SCALE)
		return (true);
	else
		return (false);
}

void	draw_minimap(t_map *map)
{
	int			x;
	int			y;
	int			move_x;
	int			move_y;
	mlx_image_t *img;

	img = map->canvas;
	move_x = (map->player.x - floor(map->player.x) - 0.5) * SCALE;
	move_y = (map->player.y - floor(map->player.y) - 0.5) * SCALE;
	y = -1;
	while (++y < map->minimap.pixel_grid_len)
	{
		x = -1;
		while (++x < map->minimap.pixel_grid_len)
		{
			if ((map->minimap.pixel_grid[y][x].type == EMPTY
				|| map->minimap.pixel_grid[y][x].type == PLAYER)
				&& is_drawable(x, y, move_x, move_y))
				mlx_put_pixel(img, x + PAD - move_x, y + PAD - move_y, BLACK);
			else if (map->minimap.pixel_grid[y][x].type == WALL
				&& is_drawable(x, y, move_x, move_y))
				mlx_put_pixel(img, x + PAD - move_x, y + PAD - move_y, GREY);
			else if (map->minimap.pixel_grid[y][x].type == CLOSED_DOOR
				&& is_drawable(x, y, move_x, move_y))
				mlx_put_pixel(img, x + PAD - move_x, y + PAD - move_y, BLUE);
			else if (map->minimap.pixel_grid[y][x].type == OPEN_DOOR 
				&& is_drawable(x, y, move_x, move_y))
				mlx_put_pixel(img, x + PAD - move_x, y + PAD - move_y, BLACK);
		}
	}
	draw_player(map);
}

void	update_minimap(t_map *map)
{
	reset_minimap(&map->minimap);
	load_minimap_grid(map);
	load_pixel_grid(&map->minimap);
	draw_minimap(map);
}
