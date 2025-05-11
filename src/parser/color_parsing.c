/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:40:42 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/05 18:55:55 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	int	r = ft_atoi(rgb[0]);
	int	g = ft_atoi(rgb[1]);
	int	b = ft_atoi(rgb[2]);

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

	components = ft_split(rgb_str, ',');
	if (!components)
		exit_error(cub, "Memory allocation failed in RGB parsing");
	if (components[0] && components[1] && components[2] && !components[3]
		&& is_valid_rgb_value(components[0])
		&& is_valid_rgb_value(components[1])
		&& is_valid_rgb_value(components[2]))
		assign_rgb_values(color, components, is_floor);
    int	i = 0;
    while (components[i])
        free(components[i++]);
    free(components);
        
}

 void assign_color(t_cub *cub, char *line, char **rgb, int *pos_flag, unsigned long *color)
{
    int i;
    char *rgb_str;
    int r, g, b;

    i = 1; // Skip identifier (e.g., "F")
    while (line[i] == ' ')
        i++;
    if (*rgb == NULL && *pos_flag == 0)
    {
        rgb_str = ft_strdup(line + i);
        if (!rgb_str)
            exit_error(cub, "Memory allocation failed for color");
        *rgb = rgb_str;
        *pos_flag = 1;
        // Parse RGB values and store in *color
       
        *color = (r << 16) | (g << 8) | b; // Combine RGB into unsigned long
    }
    else
        exit_error(cub, "Duplicate color definition");
    free(line);
}