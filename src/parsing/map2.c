/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:55 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/06 18:58:15 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_void(int i, int j, char invalid, t_cub *game)
{
    if (game->map->map_arr[0][j] == '0' || game->map->map_arr[0][j] == game->map->plyr_direction)
        return (1);
    if (game->map->map_arr[i][0] == '0' || game->map->map_arr[i][0] == game->map->plyr_direction)
        return (1);
    if (game->map->map_arr[i][j - 1] && game->map->map_arr[i][j - 1] == invalid)
        return (1);
    if (game->map->map_arr[i][j + 1] && game->map->map_arr[i][j + 1] == invalid)
        return (1);
    if (game->map->map_arr[i - 1] && game->map->map_arr[i - 1][j] == invalid)
        return (1);
    if (game->map->map_arr[i + 1] && game->map->map_arr[i + 1][j] == invalid)
        return (1);
    return (1);
}

int	check_wall(t_cub *game)
{
    int		i;
    int		j;
    char	invalid;

    i = -1;
    while (++i < game->map->map_height)
    {
        j = -1;
        while (++j < game->map->map_width)
        {
            if (game->map->map_arr[i][j] == ' ')
                invalid = '0';
            else if (game->map->map_arr[i][j] == game->map->plyr_direction)
                invalid = ' ';
            else
                continue;
            if (!check_void(i, j, invalid, game))
                return (-1); // Wall not closed
        }
    }
    return (1);
}

int	valid_characters(char **map, t_cub *game)
{
    int		player_count;
    int		i;
    int		j;

    player_count = 0;
    i = 0;
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
                return (1); // Invalid character found
            }
            if (c == 'P' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (player_count > 0)
                    return (1); // Multiple players
                player_count++;
                game->map->plyr_direction = c; // Set player direction
                game->map->plyr_counter = 1; // Mark player found
                game->map->p_x = j; // Store player position
                game->map->p_y = i;
            }
            j++;
        }
        i++;
    }
    if (player_count == 0)
    {
        printf("Error: no player found\n");
        return (1); // No player
    }
    return (0); // Valid map
}

char	*strip_newline(char *line)
{
    int	len;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return (line);
}

void	parse_file_lines(t_cub *game, int *line_count, char ***map_lines)
{
    char	*line;

    while ((line = get_next_line(game->file.filepath_len)))
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
    game->file.filepath_len = open(file, O_RDONLY);
    if (game->file.filepath_len == -1)
        exit_error(game, "Failed to open map file");
    parse_file_lines(game, &line_count, &map_lines);
    close(game->file.filepath_len);
    game->file.filepath_len = -1;
    if (!game->texture.no || !game->texture.so || !game->texture.we || !game->texture.ea)
        exit_error(game, "Missing texture");
    if (game->texture.f_color == -1 || game->texture.c_color == -1)
        exit_error(game, "Missing floor or ceiling color");
    if (line_count == 0)
        exit_error(game, "No map found");
    assign_map(game, map_lines, line_count);
    if (valid_characters(game->map->map_arr, game))
        exit_error(game, "Invalid characters in map");
    if (check_wall(game) == -1)
        exit_error(game, "Map walls are not closed");
}