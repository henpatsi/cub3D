/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:22:55 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/08 10:02:04 by hpatsi           ###   ########.fr       */
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

mlx_texture_t	*get_hit_texture(t_map *map, t_hitinfo hit)
{
	mlx_texture_t	*wall_texture;

	if (hit.side == NORTH)
		wall_texture = map->textures.north;
	if (hit.side == SOUTH)
		wall_texture = map->textures.south;
	if (hit.side == EAST)
		wall_texture = map->textures.east;
	if (hit.side == WEST)
		wall_texture = map->textures.west;
	return (wall_texture);
}
