/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:51:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/20 09:53:32 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"

#include <stdlib.h> // breaks subject, atof

# define MAX_MAP_WIDTH 1000
# define MAX_MAP_HEIGHT 1000

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

# define PI 3.141592654
# define NORMALIZE_VALUE 0.7071
# define EPSILON 1e-9

# define MOVE_SPEED 3
# define ROTATE_SPEED 200
# define MOUSE_SENSITIVITY 0.1
# define WALL_HEIGHT 400

// the closest a player can get to a wall
# define PLAYER_SIZE 0.1

// distance from player to midpoint of one of minimap sides (apothem)
# define D 10

// scale factor for scaling up minimap for drawing onto the screen
# define SCALE 10

// distance of minimap to the edge of the window
# define PAD 15

# define BLACK 0x000000ff
# define ORANGE 0xffa500ff
# define GREY 0x555555ff
# define BLUE 0x6495efff

// animation folders
# define MAXIMUM_ANIMATIONS 100
# define GUN_ANIM "textures/sprite_animations/gun/"

// door textures
# define CLOSED_DOOR_TEXTURE "textures/door/door.png"
# define DOOR_SIDES_TEXTURE "textures/door/door_sides.png"

// set to 1 to print char grid (map content) and minimap grid
# define PRINT_MAP_AND_MINIMAP 0

// set to 1 to print minimap pixel grid 
# define PRINT_ENLARGED_MINIMAP 0

// ENUMS

typedef enum e_config_flag
{
	NO_FLAG = 1 << 0,
	SO_FLAG = 1 << 1,
	WE_FLAG = 1 << 2,
	EA_FLAG = 1 << 3,
	F_FLAG = 1 << 4,
	C_FLAG = 1 << 5
}	t_config_flag;

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
	CLOSED_DOOR,
	OPEN_DOOR,
	PLAYER
}	t_gridpos_type;

// STRUCTS

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_gridpos
{
	int				x;
	int				y;
	t_gridpos_type	type;
}	t_gridpos;

typedef struct s_coords
{
	int	r;
	int	c;
}	t_coords;

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
	double			distance;
	double			x;
	double			y;
	t_wall_side		side;
	double			side_ratio;
	t_gridpos		tile_info;
	bool			hit_open_door;
	t_gridpos		open_door_info;
}	t_hitinfo;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*closed_door;
	mlx_texture_t	*door_sides;
}	t_textures;

typedef struct s_player
{
	double		x;
	double		y;
	double		x_rotation;
	t_vector	dir;
	t_vector	cam_plane;
}	t_player;

typedef struct s_minimap
{
	int			len;
	int			pixel_grid_len;
	t_gridpos	**grid;
	t_gridpos	**pixel_grid;
}	t_minimap;

typedef struct s_anim
{
	int			active;
	int			current_frame;
	double		frame_count;
	double		timer;
	double		delay;
	double		scale;
	mlx_image_t	*canvas;
	mlx_image_t	**images;
}	t_anim;

typedef struct s_draw_line_info
{
	mlx_image_t	*canvas;
	t_vector	canvas_start;
	int			height;
}	t_draw_line_info;

typedef struct s_map
{
	int			width;
	int			height;
	t_gridpos	**grid;
	t_textures	textures;
	mlx_image_t	*canvas;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_player	player;
	t_minimap	minimap;
	t_anim		animations[MAXIMUM_ANIMATIONS];
	mlx_t		*mlx;
}	t_map;

/* VALIDATION */

// validation
void			validate_input(int argc, char **argv, t_map *map);

// validation_utils
void			print_missing_config(int config_flag);
bool			check_if_config_missing(int flags);
bool			check_map_content(char *line);
bool			check_if_map_started(int flags, char *line,
					int *last_line_before_map);
void			get_map_dimensions(char *line, t_map *map,
					bool map_start_end[], int fd);

// validate_config
void			validate_non_map_elements(char *line, int *config_flag, int fd);

// init_char_grid
char			**init_char_grid(char *file, t_map *map, int map_start_line);

// validate_map
void			validate_map(char **grid, t_map *map);

// validate_map_utils
void			check_door_position(int r, int c, t_map *map, char **grid);
void			flood_fill(char **grid, t_map *map, int row, int col);

/* PREPARE MAP STRUCT */

int				load_map(t_map *map, char *map_filename);
int				load_config(t_map *map, int map_fd);
int				load_grid(t_map *map, int map_fd);
int				load_animations(mlx_t *mlx, t_anim *animations);

int				check_texture_path(char *path);

/* MINIMAP */

// init_minimap
int				init_minimap(t_map *map);

// update_minimap
void			update_minimap(t_map *map);

// load_minimap
void			load_minimap_grid(t_map *map);
void			load_pixel_grid(t_minimap *minimap);

// draw_minimap
void			draw_minimap(t_map *map);

// draw_minimap_utils
double			deg_to_rad(double degrees);
void			draw_line(t_vector v1, t_vector v2, mlx_image_t *image);

/* GAME */

// hooks
void			movement_hook(void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
void			cursor_input_hook(double xpos, double ypos, void *param);
void			update_visuals_hook(void *param);
void			animation_hook(void *param);

// hook_helpers
void			normalize_vector(t_vector	*vector);

// movement
void			move_player(t_map *map, double forward, double right);
void			rotate_player(t_map *map, double amount);

// visuals
int				init_visuals(t_map *map);
void			update_visuals(t_map *map);
void			update_animation(mlx_t *mlx, t_anim	*animation);

// draw_environment
void			draw_environment_line(t_map *map, int x, t_hitinfo hit);

// draw_environment_helpers
uint32_t		get_texture_pixel(mlx_texture_t *texture, int x, int y);
mlx_texture_t	*get_hit_texture(t_map *map, t_hitinfo hit);

// raycast
void			grid_raycast(t_hitinfo *hit, t_map *map,
					t_vector origin, t_vector direction);

// door
void			handle_door_actions(t_map *map);

/* HELPERS */

// error
int				return_error(char *message);
void			put_error_and_exit(char *message);
void			perror_and_exit(char *message);
void			non_map_error(char *message, char *line, char **split_line,
					int fd);
void			map_error(char *message, char **grid);

// error2
void			gnl_error_exit(int error);
int				gnl_error_return(int error);
void			gnl_error_free_and_exit(char **grid, int row, int gnl_error,
					int fd);
void			close_file_and_exit(int fd);

// free
void			free_grid(t_gridpos **grid);
void			free_char_grid(char **grid);
void			free_textures(t_textures textures);
void			free_animations(t_anim *animations);
void			free_all(t_map *map);

// debug
void			print_char_grid(char **grid, t_map *map);
void			print_minimap(t_minimap *minimap, bool scaled_up);

#endif