/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/24 11:57:50 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> // printf, remove later

# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "MLX42.h"

# define PI 3.141592654

# define MOVE_SPEED 10
# define ROTATE_SPEED 200

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

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
	mlx_image_t *draw;
}	t_images;

typedef struct s_gridpos
{
	int					x;
	int					y;
	t_gridpos_type		type;
}	t_gridpos;

typedef struct s_player
{
	double		x;
	double		y;
	double		x_rotation;
	t_vector	dir;
	t_vector	cam_plane;
}	t_player;

typedef struct s_map
{
	int			width;
	int			height;
	t_gridpos	**grid;
	t_images	images;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_player	player;
	mlx_t		*mlx;
}	t_map;

// PREPARE MAP

int		load_map(t_map *map, char *map_filename);
int		load_config(t_map *map, int map_fd);
int		load_grid(t_map *map, int map_fd);

// GAME

void	key_hook(mlx_key_data_t keydata, void *param);

int		init_visuals(t_map *map);
int		update_visuals(t_map *map);

// HELPERS

int		return_error(char *message);

void	free_strs(char **strs);
void	free_grid(t_gridpos **grid);

#endif