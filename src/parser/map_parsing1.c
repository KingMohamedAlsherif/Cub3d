/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:56:45 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/15 17:32:34 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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