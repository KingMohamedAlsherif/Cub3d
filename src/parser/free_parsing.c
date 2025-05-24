/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_paring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:37:09 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/21 08:45:00 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_and_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_textures(t_cub *cub)
{
	if (!cub)
		return ;
	free_and_null(&cub->textures.north);
	free_and_null(&cub->textures.south);
	free_and_null(&cub->textures.west);
	free_and_null(&cub->textures.east);
	free_and_null(&cub->c_rgb);
	free_and_null(&cub->f_rgb);
}

void	exit_error(t_cub *cub, char *msg)
{
	if (cub->fd >= 0)
		close(cub->fd);
	printf("Error\n%s\n", msg);
	exit(1);
}
