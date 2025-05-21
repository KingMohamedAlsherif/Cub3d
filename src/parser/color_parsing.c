/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:40:42 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/21 08:02:40 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_valid_rgb_value(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	assign_rgb_values(t_color *color, char **rgb, int is_floor)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return ;
	if (is_floor)
	{
		color->floor_red = r;
		color->floor_green = g;
		color->floor_blue = b;
		color->floor_color = (r << 16) | (g << 8) | b;
	}
	else
	{
		color->ceiling_red = r;
		color->ceiling_green = g;
		color->ceiling_blue = b;
		color->ceiling_color = (r << 16) | (g << 8) | b;
	}
}

void	parse_rgb(t_cub *cub, char *rgb_str, t_color *color, int is_floor)
{
	char	**components;
	int		i;

	components = ft_split(rgb_str, ',');
	if (!components)
		exit_error(cub, "Memory allocation failed in RGB parsing");
	if (components[0] && components[1] && components[2]
		&& !components[3]
		&& is_valid_rgb_value(components[0])
		&& is_valid_rgb_value(components[1])
		&& is_valid_rgb_value(components[2]))
		assign_rgb_values(color, components, is_floor);
	i = 0;
	while (components[i])
		free(components[i++]);
	free(components);
}

void	assign_color(t_cub *cub, char *line, t_color_config *cfg)
{
	int		i;
	char	*rgb_str;

	(void)cfg->color;
	i = 1;
	while (line[i] == ' ')
		i++;
	if (*(cfg->rgb) == NULL && *(cfg->pos_flag) == 0)
	{
		rgb_str = ft_strdup(line + i);
		if (!rgb_str)
			exit_error(cub, "Memory allocation failed for color");
		*(cfg->rgb) = rgb_str;
		*(cfg->pos_flag) = 1;
	}
	else
		exit_error(cub, "Duplicate color definition");
	free(line);
}
