/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:31:25 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/21 08:31:31 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	check_file_open(t_cub *game, char *file)
{
	if (map_name(file) == -1)
		exit_error(game, "Invalid map file extension");
	game->fd = open(file, O_RDONLY);
	if (game->fd == -1)
		exit_error(game, "Failed to open map file");
}

static void	check_required_elements(t_cub *game, int line_count)
{
	if (!game->no_pos || !game->so_pos || !game->we_pos || !game->ea_pos)
		exit_error(game, "Missing texture");
	if (!game->floor_pos || !game->ceiling_pos)
		exit_error(game, "Missing floor or ceiling color");
	if (line_count == 0)
		exit_error(game, "No map found");
}

void	is_parsing(t_cub *game, char *file)
{
	char	**map_lines;
	int		line_count;

	map_lines = NULL;
	line_count = 0;
	check_file_open(game, file);
	parse_file_lines(game, &line_count, &map_lines);
	close(game->fd);
	game->fd = -1;
	check_required_elements(game, line_count);
	assign_map(game, map_lines, line_count);
	if (valid_characters(game->map, game))
		exit_error(game, "Invalid characters in map");
	if (!game->p_flag)
		exit_error(game, "No player found in map");
	if (check_wall(game) == -1)
		exit_error(game, "Map walls are not closed");
}
