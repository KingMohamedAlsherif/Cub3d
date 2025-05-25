# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/05/25 18:59:17 by malsheri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	src/parser/map_parsing1.c \
                src/parser/map_parsing2.c \
                src/parser/color_parsing.c \
				src/parser/textures_parsing.c \
				src/parser/after_parsing.c \
				src/parser/final_parsing.c \
				src/parser/free_parsing.c \
				src/parser/valid_characters.c\
				src/parser/utils2.c \
                src/raycasting/raycasting.c \
                src/raycasting/move.c \
                src/raycasting/exec.c \
				src/raycasting/render.c \
				src/raycasting/render_txture.c \
                src/utils/exit.c \
                src/utils/init.c \
                src/utils/utils.c \
				src/utils/freeing.c \
                cub.c \
                GNL/get_next_line_bonus.c \
                GNL/get_next_line_utils_bonus.c

OBJS 		=	$(SRCS:.c=.o)

CC 			=	cc

CFLAGS		=	-Imlx -IGNL -Iprintf  -g3
 #-fsanitize=address -g3

LIBFT		=	libft/libft.a

PRINTF		=	printf/libftprintf.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    MLX_DIR = minilibx-linux
    MLX = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
    CFLAGS += -I$(MLX_DIR)
else
    MLX_DIR = mlx
    MLX = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
    CFLAGS += -I$(MLX_DIR)
endif

all : $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(PRINTF):
	$(MAKE) -C printf

$(NAME) : $(OBJS) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) $(LIBFT) $(MLX) $(PRINTF)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	$(MAKE) -C libft clean
	$(MAKE) -C printf clean
	rm -f $(OBJS)
        
fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C printf fclean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(NAME)
re:	fclean all

.PHONY: all clean fclean re