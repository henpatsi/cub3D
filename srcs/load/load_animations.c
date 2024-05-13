/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:25:18 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/13 18:50:48 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static mlx_image_t	*image_from_png(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (texture == 0)
	{
		ft_putstr_fd("Check that animation textures are valid\n", 2);
		return (0);
	}
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (image == 0)
		return (0);
	if (!mlx_resize_image(image, image->width * ANIM_SCALE,
			image->height * ANIM_SCALE))
	{
		ft_putstr_fd("Failed to resize animation image to given scale\n", 2);
		return (0);
	}
	return (image);
}

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

int	load_animations(mlx_t *mlx, t_anim *animation)
{
	ft_bzero(animation, sizeof(t_anim));
	animation->images = ft_calloc(FRAME_COUNT, sizeof(mlx_image_t *));
	if (animation->images == 0)
		return (-1);
	animation->images[0] = image_from_png(mlx, ANIM_FRAME_0);
	animation->images[1] = image_from_png(mlx, ANIM_FRAME_1);
	animation->images[2] = image_from_png(mlx, ANIM_FRAME_2);
	animation->images[3] = image_from_png(mlx, ANIM_FRAME_3);
	animation->images[4] = image_from_png(mlx, ANIM_FRAME_4);
	if (animation->images[0] == 0 || animation->images[1] == 0
		|| animation->images[2] == 0 || animation->images[3] == 0
		|| animation->images[4] == 0)
	{
		free(animation->images);
		return (-1);
	}
	if (init_anim_canvas(mlx, animation) == -1)
	{
		free(animation->images);
		return (-1);
	}
	animation->frame_count = FRAME_COUNT;
	animation->delay = ANIM_DELAY;
	return (1);
}
