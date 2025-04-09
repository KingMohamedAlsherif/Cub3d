# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:30:23 by amagoury          #+#    #+#              #
#    Updated: 2025/04/06 15:59:58 by malsheri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		= test2.c

OBJS 		=	$(SRCS:.c=.o)

CC 			= cc

CFLAGS	= -Wall -Werror -Wextra -Iminilibx -IGNL -Iprintf -fsanitize=address -g3

LIBFT = libft/libft.a

PRINTF = printf/libftprintf.a

MLX 	= minilibx/libmlx.a

MLX_FLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(LIBFT):	
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx

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
	$(MAKE) -C minilibx clean
	rm -rf $(NAME)

re:	fclean all
 
.PHONY: all clean fclean re