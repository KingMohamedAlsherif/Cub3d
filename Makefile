# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/05/24 13:31:30 by malsheri         ###   ########.fr        #
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

CFLAGS		=	-Imlx -IGNL -Iprintf -fsanitize=address -g3
 #-fsanitize=address -g3

LIBFT		=	libft/libft.a

PRINTF		=	printf/libftprintf.a

MLX 		=	mlx/libmlx.a

MLX_FLAGS	=	-Lmlx -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C mlx

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
	$(MAKE) -C mlx clean
	rm -rf $(NAME)
re:	fclean all

.PHONY: all clean fclean re