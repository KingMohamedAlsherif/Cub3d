/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:19:59 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/19 16:44:54 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (write(1, "(null)", 6));
	count = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (count);
}
