/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/29 11:45:44 by hpatsi           ###   ########.fr       */
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

# define PI 3.141592654

# define MOVE_SPEED 10
# define ROTATE_SPEED 400
# define WALL_HEIGHT 200

// ENUMS

typedef enum e_wall_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall_side;

typedef enum e_gridpos_type
{
	EMPTY,
	WALL,
}	t_gridpos_type;

// STRUCTS

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray_data
{
	int		grid_x;
	int		grid_y;
	double	delta_x;
	double	delta_y;
	double	dist_to_x;
	double	dist_to_y;
}	t_raydata;

typedef struct s_hitinfo
{
	double		distance;
	double		x;
	double		y;
	t_wall_side	side;
	double		side_ratio;
	bool		hit;
}	t_hitinfo;

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
	int				x;
	int				y;
	t_gridpos_type	type;
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
	// char		**grid;
	t_images	images;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
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
bool	map_started(int flags);
void	get_map_dimensions(char *line, t_map *map);

// validate/grid_init.c
char	**grid_init(char *file, t_map *map, int map_start_line);

// validate/validate_map.c
void	validate_non_map_elements(char *line, int *flags);
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

int		init_visuals(t_map *map);
int		update_visuals(t_map *map);

int		grid_raycast(t_hitinfo *hit, t_map *map, t_vector origin, t_vector direction);

// HELPERS

int		return_error(char *message);

void	free_strs(char **strs);
void	free_grid(t_gridpos **grid);

#endif