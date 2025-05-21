# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/05/21 08:51:06 by amagoury         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	src/parser/map_parsing1.c \
                src/parser/map_parsing2.c \
                src/parser/color_parsing.c \
				src/parser/textures_parsing.c \
				src/parser/after_parsing.c \
				src/parser/final_parsing.c \
				src/parser/free_paring.c \
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

CFLAGS		=	-Iminilibx_opengl -IGNL -Iprintf -fsanitize=address -g3
 #-fsanitize=address -g3

LIBFT		=	libft/libft.a

PRINTF		=	printf/libftprintf.a

MLX 		=	minilibx_opengl/libmlx.a

MLX_FLAGS	=	-Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx_opengl

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
	$(MAKE) -C minilibx_opengl clean
	rm -rf $(NAME)
re:	fclean all

.PHONY: all clean fclean re