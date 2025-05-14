/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:32:34 by amagoury          #+#    #+#             */
/*   Updated: 2024/04/21 16:49:22 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = NULL;
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			ret = (char *)s;
		s++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		ret = (char *)s;
	return (ret);
}
