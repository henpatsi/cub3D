/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:24:39 by ixu               #+#    #+#             */
/*   Updated: 2024/04/28 18:33:18 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_to_rad(double degrees)
{
	double	radians;

	radians = degrees * M_PI / 180;
	return (radians);
}

void	draw_line(t_vector v1, t_vector v2, mlx_image_t *image)
{
	double		x_steps;
	double		y_steps;
	double		max_steps;
	t_vector	current;

	x_steps = v2.x - v1.x;
	y_steps = v2.y - v1.y;
	max_steps = fmax(fabs(x_steps), fabs(y_steps));
	x_steps = x_steps / max_steps;
	y_steps = y_steps / max_steps;
	current.x = v1.x;
	current.y = v1.y;
	while ((int)(v2.x - current.x) || (int)(v2.y - current.y))
	{
		mlx_put_pixel(image, (int)current.x, (int)current.y, MAGENTA);
		current.x = current.x + x_steps;
		current.y = current.y + y_steps;
	}
}
