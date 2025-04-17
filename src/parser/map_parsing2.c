/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:55 by aishamagour       #+#    #+#             */
/*   Updated: 2025/04/17 19:27:59 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
int check_characters(char c)
{
    if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
    {
        printf("Error: invalid character '%c'\n", c);
        return (1);
    }
    return (0);
}
int valid_characters(char **map, t_cub *game)
{
    int y = 0;
    int x;

    while (map[y])
    {
        // Skip empty lines
        if (map[y][0] == '\0')
        {
            y++;
            continue;
        }

        // Check only lines that are part of the map
        if (map[y][0] == '1' || map[y][0] == '0' || map[y][0] == ' ')
        {
            x = 0;
            while (map[y][x])
            {
                if (check_characters(map[y][x])) // 1 = error
                    return (1);
                if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
                    game->player = map[y][x]; // Set player direction
                x++;
            }
        }
        y++;
    }
    return (0);
}

void is_parsing(t_cub *game, char *file)
{
    if (map_name(file) == -1)
        exit(1);

    game->map = get_map_from_file(file, game);
    
    int i = 0;
    int found_floor = 0;
    int found_ceiling = 0;

    while (game->map[i])
    {
        if (game->map[i][0] == 'F')
        {
            if (parse_floor_color(game->map[i], &game->colors) == 0)
            {
                found_floor = 1;
                // exit(1);
            }
            printf("Error: Invalid floor color\n");
        }
        else if (game->map[i][0] == 'C')
        {
            if (parse_ceiling_color(game->map[i], &game->colors) == 0)
            {
                found_ceiling = 1;
                // exit(1);
            }
            printf("Error: Invalid ceiling color\n");
        }
        i++;
    }
    printf("Floor : R:%d ", found_floor);
    printf(" Ceiling :%d ", found_ceiling);
    if (found_floor == 0 || found_ceiling == 0)
    {
        printf("Error: Missing floor or ceiling color\n");
        exit(1);
    }

    if (valid_characters(game->map, game))
    {
        printf("Error: Invalid characters in map\n");
        exit(1);
    }
    if (check_wall(game) == -1)
    {
        printf("Error: Wall not closed\n");
        exit(1);
    }
}


