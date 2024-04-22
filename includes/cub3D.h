/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/22 15:52:50 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"

// printf
# include <stdio.h>

// exit, EXIT_FAILURE
# include <stdlib.h>

// open
#include <fcntl.h>

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
	mlx_image_t *floor;
	mlx_image_t *ceiling;
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
	mlx_t		*mlx;
}	t_map;

// validate.c
void	validate_input(int argc, char **argv, t_map *map);

#endif