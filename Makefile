# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 08:30:50 by hpatsi            #+#    #+#              #
#    Updated: 2024/05/12 21:09:01 by ixu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# DIRECTORIES

OBJS_DIR = ./objs/

SRCS_DIR = ./srcs/

VALIDATE_DIR = $(SRCS_DIR)validate/

LOAD_DIR = $(SRCS_DIR)load/

GAME_DIR = $(SRCS_DIR)game/

MINIMAP_DIR = ./srcs/minimap/

# C FILES

SOURCE_FILES = main error free debug

VALIDATE_FILES_COMMON = validate validate_utils grid_init validate_error

VALIDATE_FILES_MANDATORY = validate_map validate_map_utils

VALIDATE_FILES_BONUS = validate_map_bonus validate_map_utils_bonus

MINIMAP_FILES = init_minimap update_minimap load_minimap \
				draw_minimap draw_minimap_utils

LOAD_FILES = load_map load_config load_grid load_animations

GAME_FILES = hooks hook_helpers movement visuals draw_environment \
				draw_environment_helpers raycast door

ALL_SRC_FILES = $(addsuffix .c, $(SOURCE_FILES) $(VALIDATE_FILES_COMMON) \
				$(VALIDATE_FILES_MANDATORY) $(LOAD_FILES) $(GAME_FILES) $(MINIMAP_FILES))

ALL_SRC_FILES_BONUS = $(addsuffix .c, $(SOURCE_FILES) $(VALIDATE_FILES_COMMON) \
						$(VALIDATE_FILES_BONUS) $(LOAD_FILES) $(GAME_FILES) $(MINIMAP_FILES))

OBJECTS = $(addprefix $(OBJS_DIR), $(ALL_SRC_FILES:.c=.o))

OBJECTS_BONUS = $(addprefix $(OBJS_DIR), $(ALL_SRC_FILES_BONUS:.c=.o))

# LIBRARIES

LIBFT_DIR = ./libft/

LIBFT = $(LIBFT_DIR)libft.a

MLX42_DIR = ./MLX42/build/

MLX42 = $(MLX42_DIR)libmlx42.a

# FLAGS

HEADERS = -I ./includes/ -I ./libft/ -I ./MLX42/include/MLX42/

DEPENDENCIES = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lm

CFLAGS += -Wall -Wextra -Werror $(HEADERS)

CC = cc $(CFLAGS) -g -O2

# RULES

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJECTS) $(LIBFT) $(MLX42) .base
	$(CC) $(OBJECTS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)

.base:
	rm -f .bonus
	touch .base

bonus: .bonus

.bonus: $(OBJS_DIR) $(OBJECTS_BONUS) $(LIBFT) $(MLX42)
	$(CC) $(OBJECTS_BONUS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)
	rm -f .base
	touch .bonus

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) -c -o $@ $<

$(OBJS_DIR)%.o: $(VALIDATE_DIR)%.c
	$(CC) -c -o $@ $<

$(OBJS_DIR)%.o: $(MINIMAP_DIR)%.c
	$(CC) -c -o $@ $<

$(OBJS_DIR)%.o: $(LOAD_DIR)%.c
	$(CC) -c -o $@ $<

$(OBJS_DIR)%.o: $(GAME_DIR)%.c
	$(CC) -c -o $@ $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42): $(MLX42_DIR)
	make -C $(MLX42_DIR)

$(MLX42_DIR):
	cmake ./MLX42/ -B $(MLX42_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)
	rm -f .bonus
	rm -f .base
	if [ -d $(MLX42_DIR) ]; then make clean -C $(MLX42_DIR); fi

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)
	rm -rf $(MLX42_DIR)

re: fclean all

leaks: all
	leaks -q --atExit -- ./cub3D maps/map0.cub
