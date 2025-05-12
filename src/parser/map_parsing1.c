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

void parse_cub_file(t_cub *cub, char *filename)
{
    char *line;

    cub->fd = open(filename, O_RDONLY);
    if (cub->fd < 0)
        exit_error(cub, "Cannot open file");
    while ((line = get_next_line(cub->fd))) // Use return value directly
    {
        if (line[0] && line[0] != '\n') // Skip empty lines
            textures_parsing(cub, line);
        else
            free(line); // Free empty lines
    }
    // No need to free line after loop, as get_next_line returns NULL on EOF
    // Validate textures and colors
    if (!cub->no_pos || !cub->so_pos || !cub->we_pos || !cub->ea_pos || !cub->floor_pos || !cub->ceiling_pos)
        exit_error(cub, "Missing texture or color");
    // Parse map into cub->map, cub->map_cpy, etc. (add later)
    close(cub->fd);
    cub->fd = -1;
}


 void	assign_map(t_cub *game, char **map_lines, int count)
{
	int	i;

	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		exit_error(game, "Memory allocation failed for map");
	i = -1;
	while (++i < count)
	{
		game->map[i] = ft_strdup(map_lines[i]);
		if ((int)ft_strlen(map_lines[i]) > game->cols)
			game->cols = ft_strlen(map_lines[i]);
		free(map_lines[i]);
	}
	game->map[count] = NULL;
	game->rows = count;
	free(map_lines);
}

void process_map_line(t_cub *game, char ***map_lines, int *line_count, char *line)
{
    char **new_map_lines;
    int i;

    // Allocate memory for the new array with one additional slot
    new_map_lines = malloc(sizeof(char *) * (*line_count + 1));
    if (!new_map_lines)
    {
        free(line);
        free_map_lines(*map_lines, *line_count); // Free previously allocated lines
        exit_error(game, "Memory allocation failed for map lines");
    }

    // Copy existing pointers to the new array
    for (i = 0; i < *line_count; i++)
        new_map_lines[i] = (*map_lines)[i];

    // Free the old array (but not the strings it points to)
    free(*map_lines);

    // Assign the new array to map_lines
    *map_lines = new_map_lines;

    // Add the new line to the array
    (*map_lines)[*line_count] = strip_newline(line);
    (*line_count)++;
}

void free_map_lines(char **map_lines, int line_count)
{
    for (int i = 0; i < line_count; i++)
        free(map_lines[i]);
    free(map_lines);
}