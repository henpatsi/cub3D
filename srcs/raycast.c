/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:05:12 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/25 10:56:56 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// t_vector	get_next_edge(t_vector origin, t_vector direction)
// {
	
// }

void	init_raydata(t_raydata *raydata, t_vector origin, t_vector direction)
{
	raydata->grid_x = (int) origin.x;
	raydata->grid_y = (int) origin.y;
	raydata->delta_x = fabs(1 / direction.x);
	raydata->delta_y = fabs(1 / direction.y);
	if (direction.x > 0)
		raydata->first_dist_x = (1 - origin.x - raydata->grid_x) * raydata->delta_x;
	else
		raydata->first_dist_x = (origin.x - raydata->grid_x) * raydata->delta_x;
	if (direction.y > 0)
		raydata->first_dist_y = (1 - origin.y - raydata->grid_y) * raydata->delta_y;
	else
		raydata->first_dist_y = (origin.y - raydata->grid_y) * raydata->delta_y;
}

void	get_first_edge(t_hitinfo *hit, t_map *map, t_vector direction, t_raydata *raydata)
{
	if (raydata->first_dist_y < raydata->first_dist_x)
	{
		if (direction.y > 0 && raydata->grid_y < map->height)
			raydata->grid_y += 1;
		else if (raydata->grid_y > 0)
			raydata->grid_y -= 1;
		hit->distance = raydata->first_dist_y;
	}
	else
	{
		if (direction.x > 0 && raydata->grid_x < map->width)
			raydata->grid_x += 1;
		else if (raydata->grid_x > 0)
			raydata->grid_x -= 1;
		hit->distance = raydata->first_dist_x;
	}
}

int	grid_raycast(t_hitinfo *hit, t_map *map, t_vector origin, t_vector direction)
{
	//t_vector ray;
	(void) map;

	t_raydata	raydata;

	init_raydata(&raydata, origin, direction);

	printf("distance to closest x = %f\n", raydata.first_dist_x);
	printf("distance to closest y = %f\n", raydata.first_dist_y);

	get_first_edge(hit, map, direction, &raydata);

	if (map->grid[raydata.grid_y][raydata.grid_x].type == WALL)
		return (1);

	// while (raydata.grid_y < map->height && raydata.grid_x < map->width && raydata.grid_y > 0 && raydata.grid_x > 0)
	// {
	// 	get_next_edge(origin, direction);
	// 	if (map->grid[raydata.grid_y][raydata.grid_y].type == WALL)
	// 		return (1);
	// }

	return (0);
}