/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:43:12 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/19 16:52:11 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pointer(unsigned long i)
{
	int	count ;

	count = write (1, "0x", 2);
	count += ft_alphnum_hex(i, 0);
	return (count);
}
