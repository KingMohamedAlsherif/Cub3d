# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/05/10 16:51:59 by aishamagour      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	src/parsing/parsing.c \
                src/parsing/utils.c \
                src/parsing/validate.c \
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

CFLAGS		=	-g3 -fsanitize=address -Iminilibx-linux -IGNL -Iprintf

LIBFT		=	libft/libft.a

# PRINTF		=	printf/libftprintf.a

MLX 		=	minilibx-linux/libmlx.a

MLX_FLAGS	=	-Lminilibx-linux -lmlx -lGL -lX11 -lXext -lm -lbsd

all : $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx-linux

# $(PRINTF):
# 	$(MAKE) -C printf

$(NAME) : $(OBJS) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) $(LIBFT) $(MLX) $(PRINTF)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	$(MAKE) -C libft clean
	# $(MAKE) -C printf clean
	rm -f $(OBJS)
        
fclean: clean
	$(MAKE) -C libft fclean
	# $(MAKE) -C printf fclean
	$(MAKE) -C minilibx_opengl clean
	rm -rf $(NAME)
re:	fclean all

.PHONY: all clean fclean re