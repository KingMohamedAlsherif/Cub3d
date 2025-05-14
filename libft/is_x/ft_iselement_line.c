/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iselement_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:54:04 by dehamad           #+#    #+#             */
/*   Updated: 2024/08/17 14:01:45 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is.h"

int	ft_iselement_line(char *line)
{
	while (*line)
	{
		if ((*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
			|| (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
			|| (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
			|| (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
			|| (*line == 'F' && *(line + 1) == ' ')
			|| (*line == 'C' && *(line + 1) == ' '))
			return (1);
		else
			line++;
	}
	return (0);
}
