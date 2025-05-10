/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:30:59 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/06 19:34:45 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_textures(t_cub *cub)
{
    if (cub->textures.north)
    {
        free(cub->textures.north);
        cub->textures.north = NULL;
    }
    if (cub->textures.south)
    {
        free(cub->textures.south);
        cub->textures.south = NULL;
    }
    if (cub->textures.west)
    {
        free(cub->textures.west);
        cub->textures.west = NULL;
    }
    if (cub->textures.east)
    {
        free(cub->textures.east);
        cub->textures.east = NULL;
    }
    if (cub->c_rgb)
    {
        free(cub->c_rgb);
        cub->c_rgb = NULL;
    }
    if (cub->f_rgb)
    {
        free(cub->f_rgb);
        cub->f_rgb = NULL;
    }
}

int	is_texture_or_color(char *line)
{
	if (!line)
		return (0);
	return ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ') ||
		(line[0] == 'S' && line[1] == 'O' && line[2] == ' ') ||
		(line[0] == 'W' && line[1] == 'E' && line[2] == ' ') ||
		(line[0] == 'E' && line[1] == 'A' && line[2] == ' ') ||
		(line[0] == 'F' && line[1] == ' ') ||
		(line[0] == 'C' && line[1] == ' '));
}

void exit_error(t_cub *cub, char *msg)
{
    free_textures(cub);
    if (cub->fd >= 0)
        close(cub->fd);
    printf("Error\n%s\n", msg);
    exit(1);
}

static void assign_texture(t_cub *cub, char *line, char **texture, int *    pos_flag)
{
    int i;
    char *path;

    i = 2; // Skip identifier (e.g., "NO")
    while (line[i] == ' ')
        i++;
    if (*texture == NULL && *pos_flag == 0)
    {
        path = ft_strdup(line + i);
        if (!path)
            exit_error(cub, "Memory allocation failed for texture path");
        *texture = path;
        *pos_flag = 1; // Mark texture as assigned
    }
    else
        exit_error(cub, "Duplicate texture definition");
    free(line); // Free the input line
}

t_cub *textures_parsing(t_cub *cub, char *line)
{
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
        assign_texture(cub, line, &cub->textures.north, &cub->no_pos);
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
        assign_texture(cub, line, &cub->textures.south, &cub->so_pos);
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
        assign_texture(cub, line, &cub->textures.west, &cub->we_pos);
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
        assign_texture(cub, line, &cub->textures.east, &cub->ea_pos);
    else if (line[0] == 'F' && line[1] == ' ')
        assign_color(cub, line, &cub->f_rgb, &cub->floor_pos, &cub->floor);
    else if (line[0] == 'C' && line[1] == ' ')
        assign_color(cub, line, &cub->c_rgb, &cub->ceiling_pos, &cub->ceiling);
    else
    {
        free(line);
        exit_error(cub, "Invalid texture or color definition");
    }
    return cub;
}

// validate the texture path 
// check if the path is valid 
// check if the path is a valid file 
// store the path in the dd