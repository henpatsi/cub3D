# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 08:30:50 by hpatsi            #+#    #+#              #
#    Updated: 2024/04/22 16:19:03 by ixu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# DIRECTORIES

OBJS_DIR = ./objs/

SRCS_DIR = ./srcs/

# C FILES

SOURCE_NAMES = main validate

SOURCE_FILES = $(addsuffix .c, $(SOURCE_NAMES))

SOURCES = $(addprefix $(SRCS_DIR), $(SOURCE_FILES))

OBJECTS = $(addprefix $(OBJS_DIR), $(SOURCE_FILES:.c=.o))

# LIBRARIES

LIBFT_DIR = ./libft/

LIBFT = $(LIBFT_DIR)libft.a

MLX42_DIR = ./MLX42/build/

MLX42 = $(MLX42_DIR)libmlx42.a

# FLAGS

HEADERS = -I ./includes/ -I ./libft/ -I ./MLX42/include/MLX42/

DEPENDENCIES = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

CFLAGS += -Wall -Wextra -Werror $(HEADERS)

CC = cc $(CFLAGS)

# RULES

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJECTS) $(LIBFT) $(MLX42)
	$(CC) $(OBJECTS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
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