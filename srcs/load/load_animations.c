/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:25:18 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/07 11:45:16 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_image_t	*image_from_png(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (texture == 0)
		return (0);
	image = mlx_texture_to_image(mlx, texture);
	free(texture);
	return (image);
}

int	init_anim_canvas(mlx_t *mlx, t_anim	*animation)
{
	animation->canvas = mlx_new_image(mlx, animation->images[0]->width,
			animation->images[0]->height);
	if (animation->canvas == 0)
		return (-1);
	mlx_image_to_window(mlx, animation->canvas, 200, 200);
	mlx_set_instance_depth(animation->canvas->instances, 2);
	ft_memcpy(animation->canvas->pixels, animation->images[0]->pixels,
		animation->canvas->width * animation->canvas->height * sizeof(int32_t));
	return (0);
}

int	load_animations(mlx_t *mlx, t_anim	*animation)
{
	animation->images = ft_calloc(FRAME_COUNT, sizeof(mlx_image_t *));
	animation->images[0] = image_from_png(mlx, ANIM_FRAME_0);
	animation->images[1] = image_from_png(mlx, ANIM_FRAME_1);
	animation->images[2] = image_from_png(mlx, ANIM_FRAME_2);
	animation->images[3] = image_from_png(mlx, ANIM_FRAME_3);
	animation->images[4] = image_from_png(mlx, ANIM_FRAME_4);
	if (animation->images[0] == 0 || animation->images[1] == 0
		|| animation->images[2] == 0 || animation->images[3] == 0
		|| animation->images[4] == 0)
		return (-1);
	if (init_anim_canvas(mlx, animation) == -1)
		return (-1);
	animation->active = 0;
	animation->current_frame = 0;
	animation->frame_count = FRAME_COUNT;
	animation->timer = 0;
	animation->delay = ANIM_DELAY;
	return (1);
}