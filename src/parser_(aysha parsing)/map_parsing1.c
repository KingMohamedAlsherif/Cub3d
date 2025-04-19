/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:56:45 by amagoury          #+#    #+#             */
/*   Updated: 2025/04/17 12:35:28 by aishamagour      ###   ########.fr       */
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
void get_map(char *read_map, t_cub *game)
{
    int     fd;
    char    *line;

    game->rows = 0;
    game->width = 0;
    fd = open(read_map, O_RDONLY);
    if (fd == -1)
        (write(2, "Couldn't open file\n", 19), exit(1));
    while ((line = get_next_line(fd)))
    {
        // Skip configuration lines and empty lines
        if (line[0] == '\0' || (line[0] != '1' && line[0] != '0' && line[0] != ' '))
        {
            free(line);
            continue;
        }

        game->rows++;
        if ((int)ft_strlen(line) > game->width)
            game->width = ft_strlen(line); // Update width
        free(line);
    }
    close(fd);
}
char **get_map_from_file(char *read_map, t_cub *game)
{
    int     i;
    int     fd;
    char    **map;
    char    *line;

    get_map(read_map, game); // Calculate rows and width
    map = malloc(sizeof(char *) * (game->rows + 1));
    game->map_cpy = malloc(sizeof(char *) * (game->rows + 1));
    fd = open(read_map, O_RDONLY);
    if (fd == -1)
        (write(2, "Couldn't open file\n", 19), exit(1));

    i = 0;
    while ((line = get_next_line(fd)))
    {
        // Skip configuration lines (lines that don't start with '1', '0', or ' ')
        if (line[0] != '1' && line[0] != '0' && line[0] != ' ')
        {
            free(line);
            continue;
        }

        // Process map lines
        map[i] = ft_strtrim(line, "\n");

        // Normalize row length by padding with spaces
        if ((int)ft_strlen(map[i]) < game->width)
        {
            char *padded_row = malloc(game->width + 1);
            int j = 0;
            while (j < (int)ft_strlen(map[i]))
            {
                padded_row[j] = map[i][j];
                j++;
            }
            while (j < game->width)
                padded_row[j++] = ' ';
            padded_row[j] = '\0';
            free(map[i]);
            map[i] = padded_row;
        }

        game->map_cpy[i] = ft_strdup(map[i]);
        free(line);
        i++;
    }
    map[i] = NULL;
    game->map_cpy[i] = NULL;
    close(fd);
    return (map);
}
