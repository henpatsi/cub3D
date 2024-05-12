/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:51 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/12 16:51:17 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_visuals(t_map *map)
{
	map->canvas = mlx_new_image(map->mlx, map->mlx->width,
			map->mlx->height);
	mlx_image_to_window(map->mlx, map->canvas, 0, 0);
	mlx_set_instance_depth(map->canvas->instances, 0);
	return (update_visuals(map));
}

t_vector	calculate_ray_dir(t_map *map, int x)
{
	t_vector	ray_dir;
	double		screen_position;

	screen_position = 2 * (double) x / (double) map->canvas->width - 1;
	ray_dir.x = map->player.dir.x + map->player.cam_plane.x * screen_position;
	ray_dir.y = map->player.dir.y + map->player.cam_plane.y * screen_position;
	return (ray_dir);
}

int	update_visuals(t_map *map)
{
	t_vector	origin;
	t_hitinfo	hit;
	uint32_t	x;

	origin.x = map->player.x;
	origin.y = map->player.y;
	x = 0;
	while (x < map->canvas->width)
	{
		if (grid_raycast(&hit, map, origin, calculate_ray_dir(map, x)) == 1)
			draw_environment_line(map, x, hit);
		x++;
	}
	return (1);
}

void	update_animation(mlx_t *mlx, t_anim	*animation)
{
	mlx_image_t	*frame_img;

	if (!animation->active)
		return ;
	animation->timer += mlx->delta_time;
	if (animation->timer < animation->delay)
		return ;
	animation->timer = 0;
	animation->current_frame++;
	if (animation->current_frame == animation->frame_count)
	{
		animation->active = 0;
		animation->current_frame = 0;
	}
	frame_img = animation->images[animation->current_frame];
	ft_memcpy(animation->canvas->pixels, frame_img->pixels,
		frame_img->width * frame_img->height * sizeof(int32_t));
}
