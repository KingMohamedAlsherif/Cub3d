/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:03:21 by amagoury          #+#    #+#             */
/*   Updated: 2024/03/24 15:42:59 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*check_line(char *s);
char	*del_line(char *s);
char	*read_buffer(char *str, int fd);
char	*get_next_line(int fd);
#endif