/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:29:29 by amagoury          #+#    #+#             */
/*   Updated: 2024/04/12 16:40:48 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include "../GNL/get_next_line.h"

int		ft_putchar(char c);
int		ft_putstr(char*str);
int		ft_putnbr(int nb);
int		ft_alphnum_hex(unsigned long i, int flag);
int		ft_unint(unsigned int i);
int		ft_printf(const char *st, ...);
int		type(char typ, va_list *args);
int		ft_pointer(unsigned long i);
#endif