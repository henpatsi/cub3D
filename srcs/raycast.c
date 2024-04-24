/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:05:12 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/24 14:57:08 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// t_vector	get_next_edge(t_vector origin, t_vector direction)
// {
	
// }

int	grid_raycast(t_hitinfo *hit, t_map *map, t_vector origin, t_vector direction)
{
	//t_vector ray;
	(void) hit;
	(void) map;

	int grid_x = (int) origin.x;
	int grid_y = (int) origin.y;

	double x_delta = fabs(1 / direction.x);
	double y_delta = fabs(1 / direction.y);

	printf("distance to closest y = %f\n", (origin.y - grid_y) * y_delta);
	printf("distance to closest x = %f\n", (origin.x - grid_x) * x_delta);

	// ray = get_next_edge(origin, direction);

	return (1);
}