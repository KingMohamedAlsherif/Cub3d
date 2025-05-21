/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:00:57 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/21 08:47:01 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*strip_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static char	**map_malloc(char **map_lines, int old_count)
{
	char	**new_lines;
	int		i;

	new_lines = malloc(sizeof(char *) * (old_count + 2));
	if (!new_lines)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_lines[i] = map_lines[i];
		i++;
	}
	free(map_lines);
	return (new_lines);
}

void	process_map_line(t_cub *game, char ***map_lines,
	int *line_count, char *line)
{
	char	**temp;

	temp = map_malloc(*map_lines, *line_count);
	if (!temp)
	{
		free(line);
		exit_error(game, "Memory allocation failed for map lines");
	}
	*map_lines = temp;
	(*map_lines)[*line_count] = strip_newline(line);
	(*line_count)++;
}

void	parse_file_lines(t_cub *game, int *line_count, char ***map_lines)
{
	char	*line;

	line = get_next_line(game->fd);
	while (line)
	{
		if (line[0] && line[0] != '\n')
		{
			if (is_texture_or_color(line))
				textures_parsing(game, line);
			else
				process_map_line(game, map_lines, line_count, line);
		}
		else
			free(line);
		line = get_next_line(game->fd);
	}
}
