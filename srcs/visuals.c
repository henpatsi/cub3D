/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/29 15:33:09 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_visuals(t_map *map)
{
	map->images.draw = mlx_new_image(map->mlx, map->mlx->width,
			map->mlx->height);
	mlx_image_to_window(map->mlx, map->images.draw, 0, 0);
	mlx_set_instance_depth(map->images.draw->instances, 1);
	return (update_visuals(map));
}

t_vector	calculate_ray_dir(t_map *map, int x)
{
	t_vector	ray_dir;
	double		screen_position;

	screen_position = 2 * (double) x / (double) map->images.draw->width - 1;
	ray_dir.x = map->player.dir.x + map->player.cam_plane.x * screen_position;
	ray_dir.y = map->player.dir.y + map->player.cam_plane.y * screen_position;
	return (ray_dir);
}

void	draw_vertical_line(t_map *map, t_vector start, int height,
		uint32_t color)
{
	int	y;

	y = 0;
	while (y < height)
	{
		mlx_put_pixel(map->images.draw, start.x, start.y + y, color);
		y++;
	}
}

void	draw_wall(t_map *map, int x, t_hitinfo hit)
{
	t_vector	start;
	uint32_t	color;
	uint32_t	scaled_wall_height;

	if (hit.side == NORTH)
		color = LIGHT_GREY;
		// color = 0xFF0000FF;
	if (hit.side == SOUTH)
		color = LIGHT_PEACH;
		// color = 0x00FF00FF;
	if (hit.side == EAST)
		color = PALE_PINK;
		// color = 0x0000FFFF;
	if (hit.side == WEST)
		color = PALE_GREEN;
		// color = 0xFF00FFFF;
	scaled_wall_height = (uint32_t)(WALL_HEIGHT / hit.distance);
	start.x = x;
	start.y = 0;
	if (scaled_wall_height >= map->images.draw->height)
	{
		draw_vertical_line(map, start, map->images.draw->height, color);
		return ;
	}
	else
	{
		draw_vertical_line(map, start, (map->images.draw->height / 2) - (scaled_wall_height / 2), map->ceiling_color);
		start.y += (map->images.draw->height / 2) - (scaled_wall_height / 2);
		draw_vertical_line(map, start, scaled_wall_height, color);
		start.y += scaled_wall_height;
		draw_vertical_line(map, start, map->images.draw->height - start.y, map->floor_color);
	}
}

int	update_visuals(t_map *map)
{
	t_vector	origin;
	t_hitinfo	hit;
	uint32_t	x;

	origin.x = map->player.x;
	origin.y = map->player.y;
	x = 0;
	while (x < map->images.draw->width)
	{
		if (grid_raycast(&hit, map, origin, calculate_ray_dir(map, x)) == 1)
			draw_wall(map, x, hit);
		x++;
	}
	return (1);
}
