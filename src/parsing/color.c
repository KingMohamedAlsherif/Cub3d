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

void	assign_rgb_values(t_color *color, char **rgb, int is_floor)
{
    t_atoi	r;
    t_atoi	g;
    t_atoi	b;

    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r.error || g.error || b.error || r.nbr < 0 || r.nbr > 255
        || g.nbr < 0 || g.nbr > 255 || b.nbr < 0 || b.nbr > 255)
        return ;
    if (is_floor)
    {
        color->floor_red = r.nbr;
        color->floor_green = g.nbr;
        color->floor_blue = b.nbr;
    }
    else
    {
        color->ceiling_red = r.nbr;
        color->ceiling_green = g.nbr;
        color->ceiling_blue = b.nbr;
    }
}

void	parse_rgb(t_cub *cub, char *rgb_str, t_color *color, int is_floor)
{
    char	**components;
    int		i;

    components = ft_split(rgb_str, ',');
    if (!components)
        exit_failure(cub, "Memory allocation failed in RGB parsing");
    if (components[0] && components[1] && components[2] && !components[3]
        && is_valid_rgb_value(components[0])
        && is_valid_rgb_value(components[1])
        && is_valid_rgb_value(components[2]))
        assign_rgb_values(color, components, is_floor);
    i = 0;
    while (components[i])
    {
        free(components[i]);
        i++;
    }
    free(components);
}

void	assign_color(t_cub *cub, char *line, char **rgb, int *pos_flag, int *color)
{
    int		i;
    char	*rgb_str;
    t_gnl	gnl_data;

    i = 1;
    while (line[i] == ' ')
        i++;
    if (*rgb == NULL && *pos_flag == 0)
    {
        rgb_str = ft_strdup(line + i);
        if (!rgb_str)
            exit_failure(cub, "Memory allocation failed for color");
        *rgb = rgb_str;
        *pos_flag = 1;
        parse_rgb(cub, rgb_str, &cub->texture, (*color == cub->texture.f_color));
    }
    else
        exit_failure(cub, "Duplicate color definition");
    gnl_data.line = line;
    gnl_data.error = false;
    free(gnl_data.line);
}

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