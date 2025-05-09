# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/04/17 16:51:59 by aishamagour      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		= src/parser/map_parsing1.c  src/parser/map_parsing2.c cub.c GNL/get_next_line_bonus.c GNL/get_next_line_utils_bonus.c \
				src/parser/utils.c   src/parser/color_parsing.c

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