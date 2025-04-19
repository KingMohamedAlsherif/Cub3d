# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/04/11 15:55:58 by amagoury         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		= src/parsing/parsing.c src/parsing/utils.c src/parsing/validate.c cub.c GNL/get_next_line_bonus.c GNL/get_next_line_utils_bonus.c \
				src/exec.c src/init.c src/move src/raycasting.c src/render_texture.c src/render
				
OBJS 		=	$(SRCS:.c=.o)

CC 			= cc

CFLAGS	= -Iminilibx_opengl -IGNL -Iprintf
 #-fsanitize=address -g3

LIBFT = libft/libft.a

PRINTF = printf/libftprintf.a


MLX 	= minilibx_opengl/libmlx.a

MLX_FLAGS = -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(LIBFT):	
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx_opengl

$(PRINTF):
	$(MAKE) -C printf

	
$(NAME) : $(OBJS) $(LIBFT) $(PRINTF) $(MLX)
	$(CC)	$(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) $(LIBFT) $(MLX) $(PRINTF)

%.o: %.c
	$(CC)	-c $(CFLAGS) $< -o $@

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