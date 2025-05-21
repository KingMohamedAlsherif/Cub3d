/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:56:45 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/21 08:32:11 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	map_name(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (len < 4 || ft_strncmp(&map[len - 4], ".cub", 4) != 0)
	{
		write(2, "not valid name\n", 16);
		return (-1);
	}
	return (1);
}

static void	pad_map_rows(t_cub *game)
{
	int		i;
	int		len;
	char	*new_row;

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

void	assign_map(t_cub *game, char **map_lines, int count)
{
	int	i;
	int	len;

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
		free(map_lines[i]);
	}
	game->map[count] = NULL;
	game->rows = count;
	free(map_lines);
	pad_map_rows(game);
}
