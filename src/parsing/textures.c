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

#include "../cub3d.h"

void	free_textures(t_cub *cub)
{
    if (cub->texture.no)
    {
        free(cub->texture.no);
        cub->texture.no = NULL;
    }
    if (cub->texture.so)
    {
        free(cub->texture.so);
        cub->texture.so = NULL;
    }
    if (cub->texture.we)
    {
        free(cub->texture.we);
        cub->texture.we = NULL;
    }
    if (cub->texture.ea)
    {
        free(cub->texture.ea);
        cub->texture.ea = NULL;
    }
    if (cub->texture.f_arr)
    {
        free(cub->texture.f_arr);
        cub->texture.f_arr = NULL;
    }
    if (cub->texture.c_arr)
    {
        free(cub->texture.c_arr);
        cub->texture.c_arr = NULL;
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

void	exit_error(t_cub *cub, char *msg)
{
    free_textures(cub);
    if (cub->file.filepath_len >= 0)
        close(cub->file.filepath_len);
    printf("Error\n%s\n", msg);
    exit(1);
}

static void	assign_texture(t_cub *cub, char *line, char **texture, int *pos_flag)
{
    int		i;
    char	*path;

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

t_cub	*textures_parsing(t_cub *cub, char *line)
{
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
        assign_texture(cub, line, &cub->texture.no, &cub->file.stage);
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
        assign_texture(cub, line, &cub->texture.so, &cub->file.stage);
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
        assign_texture(cub, line, &cub->texture.we, &cub->file.stage);
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
        assign_texture(cub, line, &cub->texture.ea, &cub->file.stage);
    else if (line[0] == 'F' && line[1] == ' ')
        assign_color(cub, line, &cub->texture.f_arr, &cub->file.stage, &cub->texture.f_color);
    else if (line[0] == 'C' && line[1] == ' ')
        assign_color(cub, line, &cub->texture.c_arr, &cub->file.stage, &cub->texture.c_color);
    else
    {
        free(line);
        exit_error(cub, "Invalid texture or color definition");
    }
    return (cub);
}