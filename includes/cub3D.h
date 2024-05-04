/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/30 16:43:29 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> // printf, remove later
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"

// exit, EXIT_FAILURE
# include <stdlib.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024
# define IMG_WIDTH 1024
# define IMG_HEIGHT 1024

# define PI 3.141592654

# define MOVE_SPEED 3
# define ROTATE_SPEED 200
# define WALL_HEIGHT 200

// the closest a player can get to a wall
# define PLAYER_SIZE 0.1

// distance from player to midpoint of one of minimap sides (apothem)
# define D 10

// scale factor for scaling up minimap for drawing onto the screen
# define SCALE 7

// distance of minimap to the edge of the window
# define PAD 10

# define BLACK 0x000000ff
# define MAGENTA 0xff00ffff
# define GREY 0x555555ff

# define DEBUG_MODE 1

// ENUMS

typedef enum e_flags
{
	NO_FLAG = 1 << 0,
	SO_FLAG = 1 << 1,
	WE_FLAG = 1 << 2,
	EA_FLAG = 1 << 3,
	F_FLAG  = 1 << 4,
	C_FLAG  = 1 << 5
}	t_flags;

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
	PLAYER
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

typedef	struct s_minimap
{
	int			len;
	int			pixel_grid_len;
	t_gridpos	**grid;
	t_gridpos	**pixel_grid;
}	t_minimap;

typedef struct s_map
{
	int			width;
	int			height;
	t_gridpos	**grid;
	t_images	images;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_player	player;
	t_minimap	minimap;
	mlx_t		*mlx;
}	t_map;

/* VALIDATE */
// validate.c
void	validate_input(int argc, char **argv, t_map *map);
// validate_utils.c
void	validate_non_map_elements(char *line, int *flags);
bool	map_started(int flags);
void	get_map_dimensions(char *line, t_map *map);
// grid_init.c
char	**grid_init(char *file, t_map *map, int map_start_line);
// validate_map.c
void	validate_map(char **grid, t_map *map);
// validate_map_utils.c
bool	is_closed(int r, int c, t_map *map, char **grid);
void	flood_fill(char **grid, t_map *map, int row, int col);
// validate_free.c
void	free_arr(char **arr);
void	free_initial_grid(char **grid);
// validate_error.c
void	non_map_error(char *line, char **split_line);
void	map_error(char *message, char **grid);
void	perror_and_exit(char *message);
void	put_error_and_exit(char *message);
void	put_error_free_and_exit(char *message, char **grid, int row);

// PREPARE MAP

int		load_map(t_map *map, char *map_filename);
int		load_config(t_map *map, int map_fd);
int		load_grid(t_map *map, int map_fd);

/* MINIMAP */
// init_minimap.c
int		init_minimap(t_map *map);
// reset_minimap.c
void	reset_minimap(t_minimap* minimap);
// load_minimap.c
void	load_minimap_grid(t_map *map);
void	load_pixel_grid(t_minimap *minimap);
// print_minimap.c
void	print_minimap(t_minimap *minimap, bool scaled_up);
// draw_minimap.c
void	draw_minimap(t_map *map, mlx_image_t *image);
void	reload_and_draw_minimap(t_map *map, mlx_image_t *image);
// draw_minimap_utils.c
double	deg_to_rad(double degrees);
void	draw_line(t_vector v1, t_vector v2, mlx_image_t *image);

// GAME

void	input_hook(void *param);

int		init_visuals(t_map *map);
int		update_visuals(t_map *map);

int		grid_raycast(t_hitinfo *hit, t_map *map, t_vector origin, t_vector direction);

// HELPERS

int		return_error(char *message);

void	free_strs(char **strs);
void	free_grid(t_gridpos **grid);

#endif