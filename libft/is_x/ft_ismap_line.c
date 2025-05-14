/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismap_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:57:32 by dehamad           #+#    #+#             */
/*   Updated: 2024/08/21 17:13:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is.h"

int	ft_ismap_line(char *line)
{
	if (!line || !*line)
		return (0);
	if (ft_isempty_str(line))
		return (0);
	while (*line)
	{
		if (!ft_strchr(" 01NSEW", *line))
			return (0);
		line++;
	}
	return (1);
}
