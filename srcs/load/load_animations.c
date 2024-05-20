/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:25:18 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/20 10:54:30 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


static int	init_anim_canvas(mlx_t *mlx, t_anim	*animation)
{
	int	xpos;
	int	ypos;

	animation->canvas = mlx_new_image(mlx, animation->images[0]->width,
			animation->images[0]->height);
	if (animation->canvas == 0)
		return (-1);
	xpos = mlx->width - animation->canvas->width;
	ypos = mlx->height - animation->canvas->height;
	if (mlx_image_to_window(mlx, animation->canvas, xpos, ypos) == -1)
		return (-1);
	mlx_set_instance_depth(animation->canvas->instances, 2);
	ft_memcpy(animation->canvas->pixels, animation->images[0]->pixels,
		animation->canvas->width * animation->canvas->height * sizeof(int32_t));
	return (0);
}

int	load_animation(mlx_t *mlx, t_anim *animation, char *dir)
{
	int	i;

	if (get_anim_info(animation, dir) == -1)
		return (-1);
	animation->images = ft_calloc(animation->frame_count, sizeof(mlx_image_t *));
	if (animation->images == 0)
		return (-1);
	i = 0;
	while (i < animation->frame_count)
	{
		animation->images[i] = anim_image_from_png(mlx, dir, i);
		if (animation->images[i] == 0)
		{
			free(animation->images);
			return (-1);
		}
		i++;
	}
	if (init_anim_canvas(mlx, animation) == -1)
	{
		free(animation->images);
		return (-1);
	}
	return (1);
}

int	load_animations(mlx_t *mlx, t_anim *animations)
{
	ft_bzero(animations, sizeof(t_anim) * (ANIMATION_COUNT + 1));
	if (load_animation(mlx, &animations[0], GUN_ANIM) == -1)
		return (-1);
	return (1);
}
