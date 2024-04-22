/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/22 12:41:52 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

typedef enum e_gridpos_type
{
	EMPTY,
	WALL,
}	t_gridpos_type;

typedef struct s_images
{
	mlx_image_t *north;
	mlx_image_t *south;
	mlx_image_t *east;
	mlx_image_t *west;
}	t_images;

typedef struct s_image_instances
{
	int north;
	int south;
	int east;
	int west;
}	t_imgage_instances;

typedef struct s_gridpos
{
	int					x;
	int					y;
	t_gridpos_type		type;
	t_imgage_instances	image_instances;
}	t_gridpos;

typedef struct s_map
{
	int			width;
	int			height;
	t_gridpos	**grid;
	t_images	images[1];
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	mlx_t		*mlx;
}	t_map;

int		load_map(t_map *map, char *map_filename);
int		load_config(t_map *map, int map_fd);

int		return_error(char *message);

void	free_strs(char **strs);

#endif