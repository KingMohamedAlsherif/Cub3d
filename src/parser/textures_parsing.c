/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:30:59 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/24 16:20:27 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <string.h>

int	is_texture_or_color(char *line)
{
	if (!line)
		return (0);
	return ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		|| (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		|| (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		|| (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		|| (line[0] == 'F' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' '));
}

static void	assign_texture(t_cub *cub, char *line,
	char **texture, int *pos_flag)
{
	int		i;
	char	*path;
	char	*trimmed_line;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (*texture == NULL && *pos_flag == 0)
	{
		path = ft_strdup(line + i);
		if (!path)
			exit_error(cub, "Memory allocation failed for texture path");
		trimmed_line = ft_strtrim(path, " \n");
		*texture = trimmed_line;
		free(path);
		*pos_flag = 1;
	}
	else
		exit_error(cub, "Duplicate texture definition");
	free(line);
}

static int	is_texture_line(char *line, char *id)
{
	return (line[0] == id[0] && line[1] == id[1] && line[2] == ' ');
}

static void	handle_color(t_cub *cub, char *line, int is_floor)
{
	t_color_config	cfg;

	if (is_floor)
	{
		cfg.rgb = &cub->f_rgb;
		cfg.pos_flag = &cub->floor_pos;
		cfg.color = &cub->floor;
	}
	else
	{
		cfg.rgb = &cub->c_rgb;
		cfg.pos_flag = &cub->ceiling_pos;
		cfg.color = &cub->ceiling;
	}
	assign_color(cub, line, &cfg);
}

t_cub	*textures_parsing(t_cub *cub, char *line)
{
	if (is_texture_line(line, "NO"))
		assign_texture(cub, line, &cub->textures.north, &cub->no_pos);
	else if (is_texture_line(line, "SO"))
		assign_texture(cub, line, &cub->textures.south, &cub->so_pos);
	else if (is_texture_line(line, "WE"))
		assign_texture(cub, line, &cub->textures.west, &cub->we_pos);
	else if (is_texture_line(line, "EA"))
		assign_texture(cub, line, &cub->textures.east, &cub->ea_pos);
	else if (line[0] == 'F' && line[1] == ' ')
		handle_color(cub, line, 1);
	else if (line[0] == 'C' && line[1] == ' ')
		handle_color(cub, line, 0);
	else
	{
		free(line);
		exit_error(cub, "Invalid texture or color definition");
	}
	return (cub);
}
