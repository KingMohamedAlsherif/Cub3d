# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/04/09 14:46:24 by malsheri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		= main.c player.c

OBJS 		=	$(SRCS:.c=.o)

CC 			= cc

CFLAGS	= -Wall -Werror -Wextra -Iminilibx_opengl -IGNL -fsanitize=address -g3


MLX 	= ../minilibx_opengl/libmlx.a

MLX_FLAGS = -L../minilibx_opengl -lmlx -framework OpenGL -framework AppKit

all : $(NAME)


$(MLX):
	$(MAKE) -C minilibx


	
$(NAME) : $(OBJS) $(MLX)
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
	$(MAKE) -C minilibx clean
	rm -rf $(NAME)

re:	fclean all
 
.PHONY: all clean fclean re