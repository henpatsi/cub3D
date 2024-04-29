/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:28:58 by ixu               #+#    #+#             */
/*   Updated: 2024/04/29 23:24:53 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_vectors(t_vector *vec_front_middle, \
	t_vector *vec_back_left, t_vector *vec_back_right, t_map *map)
{
	int		center;
	double	diameter;
	double	rot;

	center = map->minimap.pixel_grid_len / 2 + PAD;
	diameter = SCALE / 2;
	rot = map->player.x_rotation;
	vec_front_middle->x = center + diameter * sin(deg_to_rad(rot));
	vec_front_middle->y = center - diameter * cos(deg_to_rad(rot));
	vec_back_left->x = center - diameter * sin(deg_to_rad(120 - rot));
	vec_back_left->y = center - diameter * cos(deg_to_rad(120 - rot));
	vec_back_right->x = center + diameter * cos(deg_to_rad(30 + rot));
	vec_back_right->y = center + diameter * sin(deg_to_rad(30 + rot));
}

static void	draw_player(t_map *map, mlx_image_t *image)
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
	draw_line(vec_front_middle, vec_back_left, image);
	draw_line(vec_back_left, vec_center, image);
	draw_line(vec_center, vec_back_right, image);
	draw_line(vec_back_right, vec_front_middle, image);
}

void	draw_minimap(t_map *map, mlx_image_t *image)
{
	int		x;
	int		y;
	int		len;
	double	shift_x;
	double	shift_y;

	shift_x = (map->player.x - floor(map->player.x) - 0.5) * SCALE;
	shift_y = (map->player.y - floor(map->player.y) - 0.5) * SCALE;
	len = map->minimap.pixel_grid_len;
	y = -1;
	while (++y < len)
	{
		x = -1;
		while (++x < len)
		{
			// if ((x >= 0 && x < 5) || (y >= 0 && y < 5)
			// 	|| (x >= len - 5 && x < len) || (y >= len - 5 && y < len))
			// {
			// 	mlx_put_pixel(image, x + PAD, y + PAD, 0x80808033);
			// 	continue ;
			// }
			if (map->minimap.pixel_grid[y][x].type == EMPTY
				|| map->minimap.pixel_grid[y][x].type == PLAYER)
				{
					if (x >= shift_x + 0.5 * SCALE && x <= D * SCALE * 2 + shift_x
						&& y >= shift_y + 0.5 * SCALE && y <= D * SCALE * 2 + shift_y)
						mlx_put_pixel(image, x + PAD - shift_x, y + PAD - shift_y, BLACK);
				}
			else if (map->minimap.pixel_grid[y][x].type == WALL)
			{
				if (x >= shift_x + 0.5 * SCALE && x <= D * SCALE * 2 + shift_x
						&& y >= shift_y + 0.5 * SCALE && y <= D * SCALE * 2 + shift_y)
					mlx_put_pixel(image, x + PAD - shift_x, y + PAD - shift_y, DARK_GREY);
			}
		}
	}
	draw_player(map, image);
}

void	reload_and_draw_minimap(t_map *map,	mlx_image_t *image)
{
	init_minimap(&map->minimap);
	load_minimap_grid(map);
	load_pixel_grid(&map->minimap);
	draw_minimap(map, image);
}
