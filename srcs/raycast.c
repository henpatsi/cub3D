/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:05:12 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/25 14:08:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_raydata(t_raydata *raydata, t_vector origin, t_vector direction)
{
	raydata->grid_x = (int) origin.x;
	raydata->grid_y = (int) origin.y;
	raydata->delta_x = fabs(1 / direction.x);
	raydata->delta_y = fabs(1 / direction.y);
	if (direction.x > 0)
		raydata->dist_to_x = (raydata->grid_x + 1 - origin.x) * raydata->delta_x;
	else
		raydata->dist_to_x = (origin.x - raydata->grid_x) * raydata->delta_x;
	if (direction.y > 0)
		raydata->dist_to_y = (raydata->grid_y + 1 - origin.y) * raydata->delta_y;
	else
		raydata->dist_to_y = (origin.y - raydata->grid_y) * raydata->delta_y;
}

int	get_next_edge(t_hitinfo *hit, t_map *map, t_vector direction, t_raydata *raydata)
{
	if (raydata->dist_to_y < raydata->dist_to_x)
	{
		if (direction.y > 0)
		{
			raydata->grid_y += 1;
			hit->side = SOUTH;
		}
		else
		{
			raydata->grid_y -= 1;
			hit->side = NORTH;
		}
		hit->distance = raydata->dist_to_y;
		raydata->dist_to_y += raydata->delta_y;
	}
	else
	{
		if (direction.x > 0)
		{
			raydata->grid_x += 1;
			hit->side = WEST;
		}
		else
		{
			raydata->grid_x -= 1;
			hit->side = EAST;
		}
		hit->distance = raydata->dist_to_x;
		raydata->dist_to_x += raydata->delta_x;
	}
	if (raydata->grid_y >= map->height || raydata->grid_x >= map->width
			|| raydata->grid_y < 0 || raydata->grid_x < 0)
		return (0);
	return (1);
}

int	grid_raycast(t_hitinfo *hit, t_map *map, t_vector origin, t_vector direction)
{
	t_raydata	raydata;

	hit->distance = 0;
	hit->side = 0;

	init_raydata(&raydata, origin, direction);

	//printf("distance to closest x = %f\n", raydata.dist_to_x);
	//printf("distance to closest y = %f\n", raydata.dist_to_y);

	while (get_next_edge(hit, map, direction, &raydata))
	{
		//printf("x: %d, y: %d, grid type %d\n", raydata.grid_x, raydata.grid_y, map->grid[raydata.grid_y][raydata.grid_x].type);
		if (map->grid[raydata.grid_y][raydata.grid_x].type == WALL)
			return (1);
	}
	return (0);
}