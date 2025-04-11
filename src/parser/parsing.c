/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:56:45 by amagoury          #+#    #+#             */
/*   Updated: 2025/04/11 13:56:08 by amagoury         ###   ########.fr       */
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
void	get_map(char *read_map, t_cub *game)
{
	int		i;
	char	*lines;
	int		fd;
	(void)read_map;
	i = 1;
	game->rows = 0;
	fd = open("map.cub", O_RDONLY);
	if (fd == -1)
		(write(2, "Couldn't open file\n", 19), exit(1));
	lines = get_next_line(fd);
	while (lines)
	{
		game->rows++;
		free (lines);
		lines = get_next_line(fd);
	}
	free (lines);
	close (fd);
}

char	**get_map_from_file(char *read_map, t_cub *game)
{
	int		i;
	int		fd;
	char	**map;

	get_map (read_map, game);
	map = malloc(sizeof(char *) * (game->rows + 1));
	game->map_cpy = malloc(sizeof(char *) * (game->rows + 1));
	fd = open(read_map, O_RDONLY);
	i = -1;
	while (++i < game->rows)
	{
		map[i] = ft_strtrim(get_next_line(fd), "\n");
		game->map_cpy[i] = ft_strdup(map[i]);
	}
	map[i] = NULL;
	game->map_cpy[i] = NULL;
	close (fd);
	return (map);
}

int	check_wall(t_cub *game)
{
	int	i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1')
			return (-1);
		if (game->map[game-> height - 1][i] != '1')
			return (-1);
		i++;
	}
	i = 1;
	while (i < game->rows)
	{
		if (game->map[i][0] != '1')
			return (-1);
		if (game->map[i][game-> width - 1] != '1')
			return (-1);
		i++;
	}
	return (1);
}

void	is_parsing(t_cub *game, char *file)
{
    int	i;

	i = 0;
	if (map_name(file) == -1)
		exit(1);
	game->map = get_map_from_file(file, game);
}
