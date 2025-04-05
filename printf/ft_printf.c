/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:30:24 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/21 14:24:48 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *st, ...)
{
	int		i;
	va_list	arg;
	int		count;
	int		tmp;

	va_start (arg, st);
	i = 0;
	count = 0;
	while (st[i] != '\0')
	{
		tmp = count;
		if (st[i] == '%')
			count = count + type(st[++i], &arg);
		else
			count += ft_putchar(st[i]);
		if (count < tmp)
			return (-1);
		i++;
	}
	va_end (arg);
	return (count);
}
