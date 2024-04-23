# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 08:30:50 by hpatsi            #+#    #+#              #
#    Updated: 2024/04/23 17:20:04 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# C FILES

SOURCE_FILES = main controls load_map load_config load_grid error free

SOURCES = $(addsuffix .c, $(addprefix ./srcs/, $(SOURCE_FILES)))

OBJECTS = $(SOURCES:.c=.o)

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

$(NAME): $(OBJECTS) $(LIBFT) $(MLX42)
	$(CC) $(OBJECTS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)

%.o: %.c
	$(CC) -c -o $@ $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42): $(MLX42_DIR)
	make -C $(MLX42_DIR)

$(MLX42_DIR):
	cmake ./MLX42/ -B $(MLX42_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJECTS)
	make depend -C $(MLX42_DIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)
	rm -rf $(MLX42_DIR)

re: fclean all