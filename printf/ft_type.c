/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:44 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/17 14:08:42 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type(char typ, va_list *args)
{
	if (typ == 'c')
		return (ft_putchar(va_arg(*args, int)), 1);
	else if (typ == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (typ == 'd' || typ == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (typ == 'x')
		return (ft_alphnum_hex(va_arg(*args, unsigned int), 0));
	else if (typ == 'X')
		return (ft_alphnum_hex(va_arg(*args, unsigned int), 1));
	else if (typ == 'u')
		return (ft_unint(va_arg(*args, unsigned int)));
	else if (typ == 'p')
		return (ft_pointer(va_arg(*args, unsigned long)));
	else if (typ == '%')
		return (ft_putchar('%'));
	return (0);
}
