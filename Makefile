# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 08:30:50 by hpatsi            #+#    #+#              #
#    Updated: 2024/04/25 13:07:11 by ixu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# DIRECTORIES

OBJS_DIR = ./objs/

SRCS_DIR = ./srcs/

VALIDATE_DIR = ./srcs/validate/

# C FILES

SOURCE_FILES = main controls load_map load_config load_grid error free

VALIDATE_FILES = validate validate_utils grid_init validate_map validate_free validate_error

ALL_SRC_FILES = $(addsuffix .c, $(SOURCE_FILES)) \
			$(addsuffix .c, $(VALIDATE_FILES))

OBJECTS = $(addprefix $(OBJS_DIR), $(ALL_SRC_FILES:.c=.o))

# LIBRARIES

LIBFT_DIR = ./libft/

LIBFT = $(LIBFT_DIR)libft.a

MLX42_DIR = ./MLX42/build/

MLX42 = $(MLX42_DIR)libmlx42.a

# FLAGS

HEADERS = -I ./includes/ -I ./libft/ -I ./MLX42/include/MLX42/

DEPENDENCIES = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lm

CFLAGS += -Wall -Wextra -Werror $(HEADERS)

CC = cc $(CFLAGS) -g

# RULES

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJECTS) $(LIBFT) $(MLX42)
	$(CC) $(OBJECTS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) -c -o $@ $<

$(OBJS_DIR)%.o: $(VALIDATE_DIR)%.c
	$(CC) -c -o $@ $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42): $(MLX42_DIR)
	make -C $(MLX42_DIR)

$(MLX42_DIR):
	cmake ./MLX42/ -B $(MLX42_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -fr $(OBJS_DIR)
	make depend -C $(MLX42_DIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)
	rm -rf $(MLX42_DIR)

re: fclean all