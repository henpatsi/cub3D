/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animation_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:47:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/20 10:58:30 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

mlx_image_t	*anim_image_from_png(mlx_t *mlx, char *dir, int frame)
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

static int	open_file_in_dir(char *dir, char *filename)
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

static int	get_anim_info_line(double *field, int fd)
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