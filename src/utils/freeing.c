/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:09:39 by malsheri          #+#    #+#             */
/*   Updated: 2025/05/25 20:10:27 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_ptr(void **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}

static void	free_arr(void ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	ft_free(void *address, char target)
{
	if (!address || !target)
		return ;
	if (target == 'p')
		free_ptr((void **)address);
	else if (target == 'a')
		free_arr((void ***)address);
	else
		return ;
}
