/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:22:55 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/15 17:04:35 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	uint32_t	color;
	int			image_x_offset;
	int			image_y_offset;

	image_x_offset = x * sizeof(uint32_t);
	image_y_offset = y * texture->width * sizeof(uint32_t);
	color = 0;
	color += texture->pixels[image_y_offset + image_x_offset];
	color = color << 8;
	color += texture->pixels[image_y_offset + image_x_offset + 1];
	color = color << 8;
	color += texture->pixels[image_y_offset + image_x_offset + 2];
	color = color << 8;
	color += texture->pixels[image_y_offset + image_x_offset + 3];
	return (color);
}

static bool	next_to_door(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (false);
	if (map->grid[y][x].type == OPEN_DOOR
		|| map->grid[y][x].type == CLOSED_DOOR)
		return (true);
	return (false);
}

mlx_texture_t	*get_hit_texture(t_map *map, t_hitinfo hit)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (hit.hit_type == WALL)
	{
		if (hit.side == NORTH && !next_to_door(map, hit.y - 0.5, hit.x))
			texture = map->textures.north;
		else if (hit.side == NORTH && next_to_door(map, hit.y - 0.5, hit.x))
			texture = map->textures.door_sides;
		else if (hit.side == SOUTH && !next_to_door(map, hit.y + 0.5, hit.x))
			texture = map->textures.south;
		else if (hit.side == SOUTH && next_to_door(map, hit.y + 0.5, hit.x))
			texture = map->textures.door_sides;
		else if (hit.side == EAST && !next_to_door(map, hit.y, hit.x + 0.5))
			texture = map->textures.east;
		else if (hit.side == EAST && next_to_door(map, hit.y, hit.x + 0.5))
			texture = map->textures.door_sides;
		else if (hit.side == WEST && !next_to_door(map, hit.y, hit.x - 0.5))
			texture = map->textures.west;
		else if (hit.side == WEST && next_to_door(map, hit.y, hit.x - 0.5))
			texture = map->textures.door_sides;
	}
	else if (hit.hit_type == CLOSED_DOOR)
		texture = map->textures.closed_door;
	return (texture);
}
