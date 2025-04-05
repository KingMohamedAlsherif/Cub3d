/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:34:48 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/19 16:43:42 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
		count += ft_putstr("-2147483648");
	else if (nb < 0)
	{
		count += ft_putchar('-');
		nb *= -1;
		count += ft_putnbr(nb);
	}
	else if (nb < 10)
		count += ft_putchar (nb + 48);
	else
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(nb % 10);
	}
	return (count);
}
