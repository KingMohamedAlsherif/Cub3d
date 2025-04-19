/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:06:13 by dehamad           #+#    #+#             */
/*   Updated: 2024/08/31 16:26:53 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_free(void *address, char target)
{
	if (!address || !target)
		return ;
	if (target == 'p')
		free_ptr((void **)address);
	else if (target == 'a')
		free_arr((void ***)address);
	else
		return ;
}

int	is_color(t_cub *cub, char *line, int *color_idx, int *color_arr)
{
	if (!line || !*line)
		return (0);
	if (*line && ft_isdigit(*line))
	{
		if (*color_idx == 3)
			exit_failure(cub, "Error\nInvalid color format\n");
		use_atoi(cub, line, &color_arr[(*color_idx)]);
		return (ft_intlen(color_arr[(*color_idx)++]));
	}
	return (0);
}

bool	is_textures_ready(t_txtrs *txtrs)
{
	return (txtrs->no->img
		&& txtrs->so->img
		&& txtrs->we->img
		&& txtrs->ea->img
		&& txtrs->f_color != -1
		&& txtrs->c_color != -1);
}

void	is_player(t_cub *cub, char *map_line, int y)
{
	t_map	*map;
	int		x;

	if (!map_line || !*map_line)
		return ;
	x = 0;
	map = cub->map;
	while (map_line[x])
	{
		if (!isspace(map_line[x]) && map_line[x] != '0' && map_line[x] != '1')
		{
			if (!ft_strchr("NSWE", map_line[x]))
				exit_failure(cub, MAP_CHARS_ERR);
			map->plyr_direction = map_line[x];
			map->plyr_counter++;
			map->p_x = x;
			map->p_y = y;
			calculate_angle(cub, map_line[x], x, y);
		}
		x++;
	}
	if (map->plyr_counter > 1)
		exit_failure(cub, MAP_CHARS_ERR);
}

void	set_map_width(t_map *map, char *map_line)
{
	int	len;

	len = (int)ft_strlen(map_line);
	if (len > map->map_width)
		map->map_width = len;
}

char	*set_map_line(t_cub *cub, t_map *map, char *map_line)
{
	int		len;
	int		diff;
	char	*tmp;
	char	*fill;
	char	*res;

	len = (int)ft_strlen(map_line);
	tmp = ft_strdup(map_line);
	if (!tmp)
		exit_failure(cub, MALLOC_ERR);
	if (ft_strchr("0NSWE", map_line[0])
		|| ft_strchr("0NSWE", map_line[len - 1]))
		exit_failure(cub, MAP_WALL_ERR);
	if (len == map->map_width)
		return (tmp);
	diff = map->map_width - len;
	fill = ft_calloc(diff + 1, sizeof(char));
	if (!fill && (ft_free(&tmp, 'p'), 1))
		exit_failure(cub, MALLOC_ERR);
	while (diff--)
		fill[diff] = ' ';
	res = ft_strjoin(tmp, fill);
	if (!res && (ft_free(&tmp, 'p'), 1) && (ft_free(&fill, 'p'), 1))
		exit_failure(cub, MALLOC_ERR);
	return (ft_free(&tmp, 'p'), ft_free(&fill, 'p'), res);
}

/*
	*	is_color(t_cub *cub, char *line, int *color_idx, int *color_arr)
	{
		We use this function to parse the color from the line.
		
		Parameters:
			t_cub *cub - the main struct of the game.
			char *line - the current line we are parsing.
			int *color_idx - the index of the color we are parsing.
			int *color_arr - the array of the color we are parsing.
		
		Logic:
			-	if the line is empty or NULL, we return 0.
			-	if the first character of the line is digit, we parse the color.
			-	if the color index is 3, we exit the program.
				imagine this:
					we got indx 0, we parse the first color && ++idx => idx = 1.
					we got indx 1, we parse the second color && ++idx => idx = 2.
					we got indx 2, we parse the third color && ++idx => idx = 3.
					now if we found another digit which is a number,
					we will call this function with color_idx = 3,
					which means it's an error. i.e F 1,2,3,4
			-	if the idx is below 3 we use our use_atoi which is a wrapper fn,
				we sat the value of that color into that array with that idx.
			-	we return the length of the color 
				and we increment line len outside the function.
	}

	*	is_textures_ready(t_file *file)
	{
		We use this function to check if all the elements portion of the file
		is ready or not.
		
		Parameters:
			t_file *file - the file struct of the game.
		
		Logic:
			-	if there's any element missing we return false.
	}

	*	is_player(t_cub *cub, char *map_line)
	{
		We use this function to check if the character,
		and if that character is a valid player or not,
		also how many player character we have.
		
		Parameters:
			t_cub *cub - the main struct of the game.
			char *map_line - the current map line we are parsing.
		
		Logic:
			-	if the map line is empty or NULL, we return.
			-	if the character is not a space or not 0 or not 1,
				so it might be a player or any other character,
					-	if it's not a valid player character, we exit error.
					-	else we set the player postion
						and we increment the player counter.
			-	if the player counter is more than 1, we early exit error.
	}

	*	set_map_width(t_file *file, char *map_line)
	{
		We use this function to set the map width.
		
		Parameters:
			t_file *file - the file struct of the game.
			char *map_line - the current map line we are parsing.
		
		Logic:
			-	if the length of the map line > than the map width,
				we set the map width to that length.
	}

	*	set_map_line(t_cub *cub, t_file *file, char *map_line)
	{
		We use this function to fill the empty spaces in the map.
		
		Parameters:
			t_cub *cub - the main struct of the game.
			t_file *file - the file struct of the game.
			char *map_line - the current map line we are parsing.
		
		Logic:
			-	get the length of the map line.
			-	we create the tmp.
			-	if len == tmp => we return the tmp.
			-	else we calculate the difference between the tmp and the len.
			-	we create the fill based on the difference.
			-	we fill it with spaces.
			-	we join the tmp with the fill in the res.
			-	we return the res.
	}
*/
