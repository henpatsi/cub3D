/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/29 12:22:00 by ixu              ###   ########.fr       */
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

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024
# define IMG_WIDTH 1024
# define IMG_HEIGHT 1024

# define PI 3.141592654

# define MOVE_SPEED 20
# define ROTATE_SPEED 200
# define WALL_HEIGHT 200

// distance from player to midpoint of one of minimap sides (apothem)
# define D 10

// scale factor for scaling up minimap for drawing onto the screen
# define SCALE 10

// distance of minimap to the edge of the window
# define PAD 15

// a list of colors in hexadecimal format for testing
# define BLACK 0x000000ff
# define WHITE 0xffffffff
# define RED 0xff0000ff
# define GREEN 0x00ff00ff
# define BLUE 0x0000ffff
# define YELLOW 0xffff00ff
# define CYAN 0x00ffffff
# define MAGENTA 0xff00ffff
# define LIGHT_GREY 0xd3d3d3ff
# define MEDIUM_GREY 0x808080ff
# define DARK_GREY 0x696969ff

# define DEBUG_MODE 1

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
	int		grid_x; // the grid the ray is in
	int		grid_y;
	double	delta_x; // distance for ray from one x to next x
	double	delta_y;
	double	dist_to_x; // distance for ray from current pos to next x
	double	dist_to_y;
}	t_raydata;

typedef struct s_hitinfo
{
	double		distance;
	t_wall_side	side;
	bool		hit;
}	t_hitinfo;

typedef struct s_images
{
	mlx_image_t	*initial;
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
	t_vector	cam_plane;
}	t_player;

typedef	struct s_minimap
{
	int				len;
	int				pixel_grid_len;
	t_mini_gridpos	**grid;
	t_mini_gridpos	**pixel_grid;
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

typedef enum e_flags
{
	NO_FLAG = 1 << 0,
	SO_FLAG = 1 << 1,
	WE_FLAG = 1 << 2,
	EA_FLAG = 1 << 3,
	F_FLAG  = 1 << 4,
	C_FLAG  = 1 << 5
}	t_flags;

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
// create_minimap.c
int		create_minimap_grid(t_map *map, t_minimap *minimap);
int		create_minimap_pixel_grid(t_minimap *minimap);
// init_minimap.c
void	init_minimap(t_minimap* minimap);
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

void	key_hook(mlx_key_data_t keydata, void *param);

int		init_visuals(t_map *map);
int		update_visuals(t_map *map);

int		grid_raycast(t_hitinfo *hit, t_map *map, t_vector origin, t_vector direction);

// HELPERS

int		return_error(char *message);

void	free_strs(char **strs);
void	free_grid(t_gridpos **grid);
void	free_mini_grid(t_mini_gridpos **grid);

#endif