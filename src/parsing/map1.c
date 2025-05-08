/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:56:45 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/06 19:00:07 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_name(char *map)
{
    if ((ft_strncmp(&map[ft_strlen(map)] - 4, ".cub", 4)) != 0)
    {
        write(2, "not valid name\n", 16);
        return (-1);
    }
    return (1);
}

void	parse_cub_file(t_cub *cub, char *filename)
{
    t_gnl	gnl_data;

    cub->file.filepath_len = open(filename, O_RDONLY);
    if (cub->file.filepath_len < 0)
        exit_error(cub, "Cannot open file");
    while ((gnl_data.line = get_next_line(cub->file.filepath_len)))
    {
        if (gnl_data.line[0] && gnl_data.line[0] != '\n')
            textures_parsing(cub, gnl_data.line);
        else
            free(gnl_data.line);
    }
    if (!cub->texture.no || !cub->texture.so || !cub->texture.we
        || !cub->texture.ea || cub->texture.f_color == -1
        || cub->texture.c_color == -1)
        exit_error(cub, "Missing texture or color");
    close(cub->file.filepath_len);
    cub->file.filepath_len = -1;
}

void	assign_map(t_cub *cub, char **map_lines, int count)
{
    int	i;

    cub->map->map_arr = malloc(sizeof(char *) * (count + 1));
    if (!cub->map->map_arr)
        exit_error(cub, "Memory allocation failed for map");
    i = -1;
    while (++i < count)
    {
        cub->map->map_arr[i] = ft_strdup(map_lines[i]);
        if ((int)ft_strlen(map_lines[i]) > cub->map->map_width)
            cub->map->map_width = ft_strlen(map_lines[i]);
        free(map_lines[i]);
    }
    cub->map->map_arr[count] = NULL;
    cub->map->map_height = count;
    free(map_lines);
}

void	process_map_line(t_cub *cub, char ***map_lines, int *line_count, char *line)
{
    char	**new_map_lines;
    int		i;

    new_map_lines = malloc(sizeof(char *) * (*line_count + 1));
    if (!new_map_lines)
    {
        free(line);
        free_map_lines(*map_lines, *line_count);
        exit_error(cub, "Memory allocation failed for map lines");
    }
    i = 0;
    while (i < *line_count)
    {
        new_map_lines[i] = (*map_lines)[i];
        i++;
    }
    free(*map_lines);
    *map_lines = new_map_lines;
    (*map_lines)[*line_count] = strip_newline(line);
    (*line_count)++;
}

void	free_map_lines(char **map_lines, int line_count)
{
    int	i;

    i = 0;
    while (i < line_count)
    {
        free(map_lines[i]);
        i++;
    }
    free(map_lines);
}