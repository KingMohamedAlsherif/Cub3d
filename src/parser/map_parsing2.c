/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:55 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/15 17:36:37 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int check_void(int i, int j, char invalid, t_cub *game)
{
    if (game->map[0][j] == '0' || game->map[0][j] == game->player)
       return(1);// clean exit
    if (game->map[i][0] == '0' || game->map[i][0] == game->player)
     return(1); // clean exit
    if (game->map[i][j - 1] && game->map[i][j - 1] == invalid)
     return(1); // clean exit
    if (game->map[i][j + 1] && game->map[i][j + 1] == invalid)
     return(1); // clean exit
    if (game->map[i - 1] && game->map[i - 1][j] == invalid)
     return(1); // clean exit
    if (game->map[i + 1] && game->map[i + 1][j] == invalid)
     return(1); // clean exit
    return (1);
    // test more heavily 
}

int check_wall(t_cub *game)
{
    int i;
    int j;

    i = -1;
    j = -1;
    char invalid;
    while (++i < game->rows)
    {
        j = -1;
        while (++j < game->width)
        {
            if (game->map[i][j] == ' ')
                invalid = '0';
            else if (game->map[i][j] == game->player)
                invalid = ' ';
            else
                continue;
            if (!check_void(i , j, invalid, game))
                return (-1); // Wall not closed
        }
    }
    return (1);
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
            if (c != '1' && c != '0' && c != ' ' && c != 'P' &&
                c != 'N' && c != 'S' && c != 'E' && c != 'W')
            {
                printf("Error: invalid character '%c'\n", c);
                return 1; // Invalid character found
            }
            if (c == 'P' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (player_count > 0)
                    return 1; // Multiple players
                player_count++;
                game->player = c; // Set player direction
                game->p_flag = 1; // Mark player found
                // Optionally store player position
                // game->player_x = j;
                // game->player_y = i;
            }
            j++;
        }
        i++;
    }
    if (player_count == 0)
    {
        printf("Error: no player found\n");
        return 1; // No player
    }
    return 0; // Valid map
}

 char *strip_newline(char *line)
{
    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return line;
}

// static void    print_map(t_cub *game)
// {
//     int i = 0;
//     while (game->map[i])
//     {
//         printf("%s\n", game->map[i]);
//         i++;
//     }
// }


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

void	parse_file_lines(t_cub *game, int *line_count,
	char ***map_lines)
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
    }   free(line);

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
	if (check_wall(game) == -1)
		exit_error(game, "Map walls are not closed");
}