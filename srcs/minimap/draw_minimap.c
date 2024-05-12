/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:28:58 by ixu               #+#    #+#             */
/*   Updated: 2024/05/12 18:14:45 by ixu              ###   ########.fr       */
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

static bool	is_drawable(int x, int y, int shift_x, int shift_y)
{
	if (x >= shift_x + 0.5 * SCALE && x <= D * SCALE * 2 + shift_x + 0.5 * SCALE
		&& y >= shift_y + 0.5 * SCALE
		&& y <= D * SCALE * 2 + shift_y + 0.5 * SCALE)
		return (true);
	else
		return (false);
}

static void	draw_pixel(t_gridpos px, t_map *map, int shift_x, int shift_y)
{
	int	new_x;
	int	new_y;

	new_x = px.x + PAD - shift_x;
	new_y = px.y + PAD - shift_y;
	if ((px.type == EMPTY || px.type == PLAYER || px.type == OPEN_DOOR)
		&& is_drawable(px.x, px.y, shift_x, shift_y))
		mlx_put_pixel(map->canvas, new_x, new_y, BLACK);
	else if (px.type == WALL && is_drawable(px.x, px.y, shift_x, shift_y))
		mlx_put_pixel(map->canvas, new_x, new_y, GREY);
	else if (px.type == CLOSED_DOOR
		&& is_drawable(px.x, px.y, shift_x, shift_y))
		mlx_put_pixel(map->canvas, new_x, new_y, BLUE);
}

void	draw_minimap(t_map *map)
{
	t_gridpos	px;
	int			shift_x;
	int			shift_y;

	shift_x = (map->player.x - floor(map->player.x) - 0.5) * SCALE;
	shift_y = (map->player.y - floor(map->player.y) - 0.5) * SCALE;
	px.y = -1;
	while (++px.y < map->minimap.pixel_grid_len)
	{
		px.x = -1;
		while (++px.x < map->minimap.pixel_grid_len)
		{
			px.type = map->minimap.pixel_grid[px.y][px.x].type;
			draw_pixel(px, map, shift_x, shift_y);
		}
	}
	draw_player(map);
}
