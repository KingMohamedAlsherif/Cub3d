/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:56:45 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/24 14:09:33 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int map_name(char *map)
{
	int len;

	len = ft_strlen(map);
	if (len < 4 || ft_strncmp(&map[len - 4], ".cub", 4) != 0)
	{
		write(2, "not valid name\n", 16);
		return (-1);
	}
	return (1);
}

static void pad_map_rows(t_cub *game)
{
	int i;
	int len;
	char *new_row;

	i = 0;
	while (i < game->rows)
	{
		len = ft_strlen(game->map[i]);
		if (len < game->cols)
		{
			new_row = malloc(game->cols + 1);
			if (!new_row)
				exit_error(game,
						   "Memory allocation failed while padding map");
			ft_memcpy(new_row, game->map[i], len);
			ft_memset(new_row + len, ' ', game->cols - len);
			new_row[game->cols] = '\0';
			free(game->map[i]);
			game->map[i] = new_row;
		}
		i++;
	}
}

static void is_player(t_game *cub, char *map_line, int y)
{
	t_map *map;
	int x;

	if (!map_line || !*map_line)
		return;
	x = 0;
	map = cub->map;
	while (map_line[x])
	{
		if (map_line[x] != ' ' && map_line[x] != '0' && map_line[x] != '1')
		{
			if (!ft_strchr("NSWE", map_line[x]))
				exit_failure(cub, "MAP_CHARS_ERR");
			map->plyr_direction = map_line[x];
			map->plyr_counter++;
			map->p_x = x;
			map->p_y = y;
			// printf("Player found at (%d, %d) facing %c\n", x, y, map_line[x]);
			calculate_angle(cub, map_line[x], x, y);
		}
		x++;
	}
	if (map->plyr_counter > 1)
		exit_failure(cub, "MAP_CHARS_ERR");
}

void assign_map(t_cub *game, char **map_lines, int count, t_game *cub)
{
	int i;
	int len;

	game->cols = 0;
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		exit_error(game, "Memory allocation failed for map");
	i = -1;
	while (++i < count)
	{
		game->map[i] = ft_strdup(map_lines[i]);
		len = ft_strlen(map_lines[i]);
		if ((int)len > game->cols)
			game->cols = len;
		// Call is_player to check for player assignment
		is_player(cub, map_lines[i], i);
		free(map_lines[i]);
	}
	game->width = game->cols * TILE_SIZE;
	game->height = count * TILE_SIZE;
	game->map[count] = NULL;
	game->rows = count;
	free(map_lines);
	pad_map_rows(game);
}
