/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:09:45 by aishamagour       #+#    #+#             */
/*   Updated: 2025/04/17 19:18:57 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int is_color(char *line, int *color_idx, int *color_arr)
// {
// 	if (!line || !*line)
// 		return (0);
// 	if (ft_isdigit(*line))
// 	{
// 		if (*color_idx == 3)
// 			exit_failure("Too many color components (R, G, B only)");
// 		ft_atoi(&color_arr[(*color_idx)]);
// 		return (ft_intlen(color_arr[(*color_idx)++]));
// 	}
// 	return (0);
// }
 static char *skip_identifier(char *line)
{
    // Skip whitespace
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
    
    // Skip F or C identifier
    if (*line && (*line == 'F' || *line == 'C'))
        line++;
    
    // Skip whitespace again
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
    
    return line;
}

int is_color(char *line, int *color_idx, int *color_arr)
{
	int i = 0;
	int color_value = 0;

	while (line[i] && ft_isdigit(line[i]))
	{
		color_value = color_value * 10 + (line[i] - '0');
		i++;
	}
	if (color_value < 0 || color_value > 255)
		exit_failure("Color value out of range (0-255)");
	color_arr[*color_idx] = color_value;
	return (i);
}

int parse_floor_color(char *line, t_color *color)
{
	line = skip_identifier(line);
    validate_color_string(line);
	int color_arr[3];
	int color_idx = 0;
	int i = 0;

	while (line[i])
	{
		i += is_color(&line[i], &color_idx, color_arr);
		if (line[i] == ',')
			i++;
		else if (line[i] != '\0' && !ft_isdigit(line[i]))
		{
			// exit_failure("Invalid character in color string");
			return(1);
		}
			
	}
	if (color_idx != 3){
		// exit_failure("Incomplete color string");
		return(1);
	}
	color->floor_red = color_arr[0];
	color->floor_green = color_arr[1];
	color->floor_blue = color_arr[2];
	return (0);
}

int  parse_ceiling_color(char *line, t_color *color)
{
	line = skip_identifier(line);
    validate_color_string(line);
	int color_arr[3];
	int color_idx = 0;
	int i = 0;

	while (line[i])
	{
		i += is_color(&line[i], &color_idx, color_arr);
		if (line[i] == ',')
			i++;
		else if (line[i] != '\0' && !ft_isdigit(line[i]))
		{
			// exit_failure("Invalid character in ceiling color string");
			return(1);
		}
	}
	if (color_idx != 3)
	{
		// exit_failure("Incomplete ceiling color");
		return(1);
	}
	color->ceiling_red = color_arr[0];
	color->ceiling_green = color_arr[1];
	color->ceiling_blue = color_arr[2];
	return (0);
}

int  validate_color_string(const char *line)
{
    printf("Validating color string: '%s'\n", line); // Add debug print
    int i = 0;
    int comma_count = 0;

    if (!line || !*line)
        exit_failure("Empty color string");
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    while (line[i])
    {
        if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' ' && line[i] != '\t')
        {
            printf("Invalid character found: '%c' at position %d\n", line[i], i);
            // exit_failure("Invalid character in color string");
		}
        if (line[i] == ' ' || line[i] == '\t')
        {
            i++;
            continue;
        }
        if (line[i] == ',' && line[i + 1] == ',')
            // exit_failure("Invalid color format: double commas");
        if (line[i] == ',')
            comma_count++;
        i++;
    }
    if (comma_count != 2)
        // exit_failure("Color format error: must have exactly two commas");
		printf("Comma count: %d\n", comma_count);
    if (line[0] == ',' || line[i - 1] == ',')
        // exit_failure("Color format error: can't start or end with comma");
		printf("Color string can't start or end with comma\n");
}
