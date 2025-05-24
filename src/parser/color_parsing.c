/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:40:42 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/24 10:28:21 by malsheri         ###   ########.fr       */
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
	// printf("RGB values: %d, %d, %d\n", r, g, b);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_error(NULL, "RGB values must be between 0 and 255");
	if (is_floor)
	{
		color->floor_red = r;
		color->floor_green = g;
		color->floor_blue = b;
		color->floor_color = (r << 16) | (g << 8) | b;
		// printf("Floor color: %d\n", color->floor_color);
	}
	else
	{
		color->ceiling_red = r;
		color->ceiling_green = g;
		color->ceiling_blue = b;
		color->ceiling_color = (r << 16) | (g << 8) | b;
		// printf("Ceiling color: %d\n", color->ceiling_color);
	}
}

void	parse_rgb(t_cub *cub, char *rgb_str, t_color *color, int is_floor)
{
	char	**components;
	int		i;

	components = ft_split(rgb_str, ',');
	// for (i = 0; components[i]; i++)
	// {
	// 	printf("Component %d: %s\n", i, components[i]);
	// 	// components[i] = ft_strtrim(components[i], " \n");
	// 	// if (ft_strlen(components[i]) == 0)
	// 	// 	break ;
	// }
	if (!components)
		exit_error(cub, "Memory allocation failed in RGB parsing");
	if (components[0] && components[1] && components[2]
		&& !components[3]
		&& is_valid_rgb_value(components[0])
		&& is_valid_rgb_value(components[1])
		&& is_valid_rgb_value(components[2]))
		{
			// printf("All RGB values are valid\n");
			assign_rgb_values(color, components, is_floor);
		}
	// printf("Parsed RGB values: %d, %d, %d\n",
	// 	color->floor_red, color->floor_green, color->floor_blue);
	// printf("Color value: %d\n", color->floor_color);
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
		rgb_str = ft_strtrim(rgb_str, " \n");
		*(cfg->rgb) = rgb_str;
		*(cfg->pos_flag) = 1;
	}
	else
		exit_error(cub, "Duplicate color definition");
	free(line);
}

// static void validate_elements(t_cub *cub, char *line)
// {
// 	t_file *file;
// 	t_txtrs *txtrs;
// 	size_t len;

// 	file = &cub->file;
// 	txtrs = cub->txtrs;
// 	len = ft_strlen(line);
// 	if (ft_strnstr(line, "NO", len))
// 		validate_img(cub, txtrs->no, line);
// 	else if (ft_strnstr(line, "SO", len))
// 		validate_img(cub, txtrs->so, line);
// 	else if (ft_strnstr(line, "WE", len))
// 		validate_img(cub, txtrs->we, line);
// 	else if (ft_strnstr(line, "EA", len))
// 		validate_img(cub, txtrs->ea, line);
// 	else if (ft_strnstr(line, "F", len))
// 		validate_color(cub, txtrs->f_arr, &txtrs->f_color, line);
// 	else if (ft_strnstr(line, "C", len))
// 		validate_color(cub, txtrs->c_arr, &txtrs->c_color, line);
// 	if (is_textures_ready(cub->txtrs))
// 		file->stage++;
// }

// static void validate_color(t_cub *cub, int *arr, int *value, char *line)
// {
// 	int colors_counter;
// 	int commas_counter;
// 	int letters_counter;

// 	colors_counter = 0;
// 	commas_counter = 0;
// 	letters_counter = 0;
// 	while (*line)
// 	{
// 		while (*line && ft_isspace(*line))
// 			line++;
// 		line += ft_iscomma(*line, &commas_counter);
// 		if (commas_counter > colors_counter)
// 			exit_failure(cub, COLOR_ERR);
// 		line += ft_isletter(*line, &letters_counter);
// 		line += is_color(cub, line, &colors_counter, arr);
// 		if (colors_counter == 3 && commas_counter != 2)
// 			exit_failure(cub, COLOR_ERR);
// 		if (letters_counter > 1 || commas_counter > 2 || colors_counter > 3)
// 			exit_failure(cub, COLOR_ERR);
// 	}
// 	if (*value != -1 || letters_counter != 1 || commas_counter != 2 || colors_counter != 3)
// 		exit_failure(cub, COLOR_ERR);
// 	*value = create_rgb(arr);
// }
