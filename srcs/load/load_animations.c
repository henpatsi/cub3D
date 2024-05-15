/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:25:18 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/15 09:56:30 by hpatsi           ###   ########.fr       */
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






char	*get_anim_image_path(char *dir, int frame)
{
	char	*frame_str;
	char	*filename;
	char	*path;

	frame_str = ft_itoa(frame);
	if (frame_str == 0)
		return (0);
	filename = ft_strjoin(frame_str, ".png");
	free(frame_str);
	if (filename == 0)
		return (0);
	path = ft_strjoin(dir, filename);
	free(filename);
	if (path == 0)
		return (0);
	return (path);
}

static mlx_image_t	*anim_image_from_png(mlx_t *mlx, char *dir, int frame)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	char			*path;
	
	path = get_anim_image_path(dir, frame);
	texture = mlx_load_png(path);
	if (texture == 0)
	{
		ft_putstr_fd("Error\nUnable to load animation texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (image == 0)
		return (0);
	return (image);
}


int	open_file_in_dir(char *dir, char *filename)
{
	int		fd;
	char	*file_path;

	file_path = ft_strjoin(dir, filename);
	if (file_path == 0)
		return (-1);
	fd = open(file_path, O_RDONLY);
	free(file_path);
	return (fd);
}

int	get_anim_info_line(double *field, int fd)
{
	char	*line;
	char	**split;
	int		gnl_error;

	line = get_next_line(fd, &gnl_error);
	if (line == 0)
		return (-1);
	split = ft_split(line, ' ');
	free(line);
	if (split == 0)
		return (-1);
	if (split[0] == 0 || split[1] == 0)
	{
		ft_freestrs(split);
		return (-1);
	}
	*field = atof(split[1]);
	ft_freestrs(split);
	return (1);
}

int	get_anim_info(t_anim *animation, char *dir)
{
	int		fd;

	fd = open_file_in_dir(dir, "anim.info");
	if (fd == -1)
		return (-1);
	if (get_anim_info_line(&animation->delay, fd) == -1
		|| get_anim_info_line(&animation->frame_count, fd) == -1
	 	|| get_anim_info_line(&animation->scale, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
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
	ft_bzero(animations, sizeof(t_anim) * MAXIMUM_ANIMATIONS);
	if (load_animation(mlx, &animations[0], GUN_ANIM) == -1)
		return (-1);
	return (1);
}
