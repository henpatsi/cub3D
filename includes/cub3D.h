/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/27 16:35:54 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> // printf, remove later

// open
# include <fcntl.h>

# include <math.h>

# include "libft.h"
# include "MLX42.h"

// exit, EXIT_FAILURE
# include <stdlib.h>

# define WIN_WIDTH 512
# define WIN_HEIGHT 512
# define IMG_WIDTH 512
# define IMG_HEIGHT 512

# define PI 3.141592654

# define MOVE_SPEED 10
# define ROTATE_SPEED 200

// distance from player to midpoint of one of minimap sides (apothem)
# define APO 5

// scale factor for scaling up minimap for drawing onto the screen
# define SCALE 10

# define DEBUG_MODE 1

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef enum e_gridpos_type
{
	EMPTY,
	WALL,
	PLAYER
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

typedef struct s_mini_gridpos
{
	int					x;
	int					y;
	t_gridpos_type		type;
}	t_mini_gridpos;

typedef struct s_player
{
	double		x;
	double		y;
	double		x_rotation;
	t_vector	dir;

}	t_player;

typedef	struct s_minimap
{
	int				len;
	t_mini_gridpos	**grid;
	t_player		player;
}	t_minimap;

typedef struct s_map
{
	int			width;
	int			height;
	t_gridpos	**grid;
	// char		**grid;
	t_images	images;
	t_player	player;
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

// validate/validate.c
void	validate_input(int argc, char **argv, t_map *map);

// validate/validate_utils.c
void	validate_non_map_elements(char *line, int *flags);
bool	map_started(int flags);
void	get_map_dimensions(char *line, t_map *map);

// validate/grid_init.c
char	**grid_init(char *file, t_map *map, int map_start_line);

// validate/validate_map.c
void	validate_map(char **grid, t_map *map);

// validate/validate_map_utils.c
bool	is_closed(int r, int c, t_map *map, char **grid);
void	flood_fill(char **grid, t_map *map, int row, int col);

// validate/free.c
void	free_arr(char **arr);
void	free_initial_grid(char **grid);

// validate/error.c
void	non_map_error(char *line, char **split_line);
void	map_error(char *message, char **grid);
void	perror_and_exit(char *message);
void	put_error_and_exit(char *message);
void	put_error_free_and_exit(char *message, char **grid, int row);

// PREPARE MAP

int		load_map(t_map *map, char *map_filename);
int		load_config(t_map *map, int map_fd);
int		load_grid(t_map *map, int map_fd);

// GAME

void	key_hook(mlx_key_data_t keydata, void *param);

// HELPERS

int		return_error(char *message);

void	free_strs(char **strs);
void	free_grid(t_gridpos **grid);
void	free_mini_grid(t_mini_gridpos **grid);

#endif