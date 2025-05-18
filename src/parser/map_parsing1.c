/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:56:45 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/18 17:48:29 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	map_name(char *map)
{
	int len = ft_strlen(map);

	if (len < 4 || ft_strncmp(&map[len - 4], ".cub", 4) != 0)
	{
		write(2, "not valid name\n", 16);
		return (-1);
	}
	return (1);
}


void parse_cub_file(t_cub *cub, char *filename)
{
	char *line;
	char *trimmed;

	cub->fd = open(filename, O_RDONLY);
	if (cub->fd < 0)
		exit_error(cub, "Cannot open file");

	while ((line = get_next_line(cub->fd)))
	{
		trimmed = ft_strtrim(line, " \t\n"); // Remove leading/trailing whitespace
		if (trimmed[0]) // Only process non-empty lines
			textures_parsing(cub, trimmed);
		free(trimmed);
		free(line);
	}

	if (!cub->no_pos || !cub->so_pos || !cub->we_pos || !cub->ea_pos
		|| !cub->floor_pos || !cub->ceiling_pos)
		exit_error(cub, "Missing texture or color");

	close(cub->fd);
	cub->fd = -1;
}

 static void pad_map_rows(t_cub *game)
{
	int i;
	char *new_row;

	i = 0;
	while (i < game->rows)
	{
		int len = ft_strlen(game->map[i]);
		if (len < game->cols)
		{
			new_row = malloc(game->cols + 1);
			if (!new_row)
				exit_error(game, "Memory allocation failed while padding map");

			ft_memcpy(new_row, game->map[i], len);
			ft_memset(new_row + len, ' ', game->cols - len); // fill remaining with spaces
			new_row[game->cols] = '\0';

			free(game->map[i]);
			game->map[i] = new_row;
		}
		i++;
	}
}


void	assign_map(t_cub *game, char **map_lines, int count)
{
	int	i;

	game->cols = 0; // Important: reset before calculating
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
	pad_map_rows(game);
}

