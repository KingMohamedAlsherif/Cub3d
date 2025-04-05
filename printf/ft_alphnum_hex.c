/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alphnum_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:47:26 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/21 14:23:45 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_alphnum_hex(unsigned long i, int flag)
{
	int		a;
	int		j;
	char	hex[40];
	char	*hnum;

	a = 0;
	if (flag)
		hnum = "0123456789ABCDEF";
	else
		hnum = "0123456789abcdef";
	j = 0;
	if (!i)
		return (write(1, "0", 1));
	while (i != 0)
	{
		hex[a++] = hnum[i % 16];
		i = i / 16;
	}
	j = a;
	while (a-- > 0)
		ft_putchar(hex[a]);
	return (j);
}
