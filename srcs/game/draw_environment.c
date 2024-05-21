/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:12:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/21 20:20:08 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_vertical_color(t_draw_line_info dli, uint32_t color)
{
	int	y;

	y = 0;
	while (y < dli.height && dli.height
			&& dli.canvas_start.y + y < dli.canvas->height)
	{
		mlx_put_pixel(dli.canvas, dli.canvas_start.x,
			dli.canvas_start.y + y, color);
		y++;
	}
}

static void	draw_vertical_texture(t_draw_line_info dli, mlx_texture_t *texture,
		t_vector image_start)
{
	int		y;
	double	ratio;
	int		texture_y;

	y = 0;
	while (y < dli.height && dli.canvas_start.y + y < dli.canvas->height)
	{
		ratio = (double) y / (double) dli.height;
		texture_y = ((texture->height - 1 - image_start.y) * ratio)
			+ image_start.y;
		mlx_put_pixel(dli.canvas, dli.canvas_start.x, dli.canvas_start.y + y,
			get_texture_pixel(texture, image_start.x, texture_y));
		y++;
	}
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
	image_start.y = 0;

	dli.height = ((double)map->canvas->height - (double)wall_height) / 2 + (map->player.y_rotation * 4);
	if (dli.height < 0)
	{
		double ratio = (double)-dli.height / (double) wall_height;
		image_start.y = floor(ratio * wall_texture->height);
		wall_height += dli.height;
		dli.height = 0;
	}
	draw_vertical_color(dli, map->ceiling_color);
	dli.canvas_start.y += dli.height;

	if (dli.canvas_start.y + wall_height > map->canvas->height)
		dli.height = map->canvas->height - dli.canvas_start.y;
	else
		dli.height = wall_height;
	draw_vertical_texture(dli, wall_texture, image_start);

	dli.canvas_start.y += dli.height;
	
	dli.height = map->canvas->height - dli.canvas_start.y;
	draw_vertical_color(dli, map->floor_color);
}
