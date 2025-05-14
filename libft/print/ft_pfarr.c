/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfarr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:02:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/08/19 14:58:12 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_pfarr(t_fmt *fmt)
{
	char	**arr;
	char	*str;
	size_t	len;
	int		index;

	arr = va_arg(fmt->args, char **);
	index = 0;
	if (!arr)
		return (ft_putstr_fd("(null)\n", fmt->fd));
	while (arr[index])
	{
		str = arr[index];
		len = ft_strlen(str);
		fmt->len += ft_strlen(arr[index]);
		if (len)
		{
			ft_putchar_fd('.', fmt->fd);
			ft_putstr_fd(arr[index++], fmt->fd);
			ft_putchar_fd('.', fmt->fd);
		}
		else if (++index)
			ft_putchar_fd(' ', fmt->fd);
		if (str[len - 1] && str[len - 1] != '\n')
			ft_putchar_fd('\n', fmt->fd);
	}
}
