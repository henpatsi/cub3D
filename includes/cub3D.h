/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/25 11:05:37 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"

// printf
# include <stdio.h> // to be removed?

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

typedef enum e_flags
{
	NO_FLAG = 1 << 0,
	SO_FLAG = 1 << 1,
	WE_FLAG = 1 << 2,
	EA_FLAG = 1 << 3,
	F_FLAG  = 1 << 4,
	C_FLAG  = 1 << 5
}	t_flags;

// validate.c
void	validate_input(int argc, char **argv, t_map *map);

// validate_utils.c
bool	map_started(int flags);
void	get_map_dimensions(char *line, t_map *map);

// grid_init.c
char	**grid_init(char *file, t_map *map, int map_start_line);

// validate_map.c
void	validate_non_map_elements(char *line, int *flags);
void	validate_map(char **grid, t_map *map);

// free.c
void	free_arr(char **arr);
void	free_grid(char **grid);

// error.c
void	non_map_error(char *line, char **split_line);
void	map_error(char *message, char **grid);
void	perror_and_exit(char *message);
void	put_error_and_exit(char *message);
void	put_error_free_and_exit(char *message, char **grid, int row);

#endif