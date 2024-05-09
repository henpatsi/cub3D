/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:12:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/09 12:23:01 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_vertical_color(t_draw_line_info dli, uint32_t color)
{
	int	y;

	y = 0;
	while (y < dli.height)
	{
		mlx_put_pixel(dli.canvas, dli.canvas_start.x,
			dli.canvas_start.y + y, color);
		y++;
	}
}

void	draw_vertical_texture(t_draw_line_info dli, mlx_texture_t *texture,
		t_vector image_start)
{
	int		y;
	double	ratio;
	int		texture_y;

	y = 0;
	while (y < dli.height)
	{
		ratio = (double) y / (double) dli.height;
		texture_y = ((texture->height - 1 - (2 * image_start.y)) * ratio)
			+ image_start.y;
		mlx_put_pixel(dli.canvas, dli.canvas_start.x, dli.canvas_start.y + y,
			get_texture_pixel(texture, image_start.x, texture_y));
		y++;
	}
}

void	draw_fs_wall_line(t_draw_line_info dli,
		uint32_t wall_height, t_vector image_start,
		mlx_texture_t *wall_texture)
{
	image_start.y = ((double)(wall_height - dli.canvas->height) / 2)
		/ (double) wall_height * (double) wall_texture->height;
	dli.height = dli.canvas->height;
	draw_vertical_texture(dli, wall_texture, image_start);
}

void	draw_environment_line(t_map *map, int x, t_hitinfo hit)
{
	t_draw_line_info	dli;
	t_vector			image_start;
	mlx_texture_t		*wall_texture;
	uint32_t			wall_height;

	dli.canvas = map->canvas;
	dli.canvas_start.x = x;
	dli.canvas_start.y = 0;
	wall_texture = get_hit_texture(map, hit);
	wall_height = (uint32_t)(WALL_HEIGHT / hit.distance);
	image_start.x = round(hit.side_ratio * (double) wall_texture->width);
	if (wall_height >= map->canvas->height)
		draw_fs_wall_line(dli, wall_height, image_start, wall_texture);
	else
	{
		dli.height = (map->canvas->height / 2) - (wall_height / 2);
		draw_vertical_color(dli, map->ceiling_color);
		dli.canvas_start.y += dli.height;
		dli.height = wall_height;
		image_start.y = 0;
		draw_vertical_texture(dli, wall_texture, image_start);
		dli.canvas_start.y += dli.height;
		dli.height = map->canvas->height - dli.canvas_start.y;
		draw_vertical_color(dli, map->floor_color);
	}
}
