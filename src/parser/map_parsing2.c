/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:55 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/18 17:51:08 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
static int is_invalid_neighbor(char center, char neighbor, char player)
{
    // Invalid if 0 or player next to space
    if ((center == '0' || center == player) && neighbor == ' ')
        return 1;
    // Invalid if space next to 0 or player
    if (center == ' ' && (neighbor == '0' || neighbor == player))
        return 1;
    return 0;
}

// Check if position (i, j) is adjacent to an invalid character
int check_void(int i, int j, t_cub *game)
{
    char c = game->map[i][j];

    // Check if on any border
    if (i == 0 || j == 0 || i == game->rows - 1 || j == game->cols - 1)
    {
        if (c == '0' || c == game->player)
            return 0; // Invalid: on open edge
    }

    // Check adjacent cells
    if ((j > 0 && is_invalid_neighbor(c, game->map[i][j - 1], game->player)) ||
        (j < game->cols - 1 && is_invalid_neighbor(c, game->map[i][j + 1], game->player)) ||
        (i > 0 && is_invalid_neighbor(c, game->map[i - 1][j], game->player)) ||
        (i < game->rows - 1 && is_invalid_neighbor(c, game->map[i + 1][j], game->player)))
    {
        return 0;
    }

    return 1;
}




// Check if all walls are closed
int check_wall(t_cub *game)
{
    int i = 0;
    int j;

    while (i < game->rows)
    {
        j = 0;
        while (j < game->cols)
        {
            char c = game->map[i][j];
            if (c == '0' || c == ' ' || c == game->player)
            {
                if (!check_void(i, j, game))
                {
                    fprintf(stderr, "Error: Map is not closed at position (%d, %d)\n", i, j);
                    return -1;
                }
            }
            j++;
        }
        i++;
    }
    return 1;
}


int valid_characters(char **map, t_cub *game)
{
    int player_count = 0;
    int i = 0;
    int j;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            char c = map[i][j];
            if (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
            {
                printf("Error: invalid character '%c'\n", c);
                return 1;
            }
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (player_count > 0)
                    return 1;
                player_count++;
                game->player = c;
                game->p_flag = 1;
            }
            j++;
        }
        i++;
    }
    if (player_count == 0)
    {
        printf("Error: no player found\n");
        return 1;
    }
    return 0;
}


char *strip_newline(char *line)
{
    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return line;
}




 void	process_map_line(t_cub *game, char ***map_lines,
	int *line_count, char *line)
{
	char	**temp;

	temp = realloc(*map_lines, sizeof(char *) * (*line_count + 1));
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

	while ((line = get_next_line(game->fd)))
    {
	    if (line[0] && line[0] != '\n')
	    {
		    if (is_texture_or_color(line))
			    textures_parsing(game, line);
		    else
			    process_map_line(game, map_lines, line_count, line);
	    }
	    else
		    free(line); // Free empty lines
    }
}



void	is_parsing(t_cub *game, char *file)
{
	char	**map_lines;
	int		line_count;

	map_lines = NULL;
	line_count = 0;
	if (map_name(file) == -1)
		exit_error(game, "Invalid map file extension");

	game->fd = open(file, O_RDONLY);
	if (game->fd == -1)
		exit_error(game, "Failed to open map file");

	parse_file_lines(game, &line_count, &map_lines);
	close(game->fd);
	game->fd = -1;

	if (!game->no_pos || !game->so_pos || !game->we_pos || !game->ea_pos)
		exit_error(game, "Missing texture");
	if (!game->floor_pos || !game->ceiling_pos)
		exit_error(game, "Missing floor or ceiling color");
	if (line_count == 0)
		exit_error(game, "No map found");

	assign_map(game, map_lines, line_count);

	if (valid_characters(game->map, game))
		exit_error(game, "Invalid characters in map");

	if (!game->p_flag)
		exit_error(game, "No player found in map");

	if (check_wall(game) == -1)
		exit_error(game, "Map walls are not closed");
}
