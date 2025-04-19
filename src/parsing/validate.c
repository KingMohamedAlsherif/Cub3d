/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:56:17 by dehamad           #+#    #+#             */
/*   Updated: 2024/08/31 14:52:39 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_img(t_cub *cub, t_txtdata *txtr, char *line);
static void	validate_color(t_cub *cub, int *arr, int *value, char *line);
static void	validate_elements(t_cub *cub, char *line);
static void	validate_map(t_cub *cub, t_file *file, t_map *map, int st);

void	file_validate(t_cub *cub, t_file *file, t_map *map)
{
	char	**file_arr;
	int		i;

	file_arr = file->file_arr;
	i = 0;
	while (file->stage == 1 && file_arr[i])
	{
		if (ft_isempty_str(file_arr[i]))
			i++;
		else if (ft_iselement_line(file_arr[i]))
			validate_elements(cub, file_arr[i++]);
		else
			exit_failure(cub, ELEMENTS_ERR);
	}
	while (file->stage == 2 && file_arr[i])
	{
		while (file_arr[i] && ft_isempty_str(file_arr[i]))
			i++;
		if (!map->map_st && !ft_iselement_line(file_arr[i]))
			map->map_st = i++;
		else
			break ;
	}
	map->map_end = file->file_len;
	validate_map(cub, file, map, map->map_st);
}

static void	validate_img(t_cub *cub, t_txtdata *txtr, char *line)
{
	char	**split;
	int		width;
	int		height;

	if (txtr->img)
		exit_failure(cub, ELEMENTS_EXIST_ERR);
	split = ft_split(line, ' ');
	if (!split)
		exit_failure(cub, MALLOC_ERR);
	if ((!split[0] || !split[1] || split[2]) && (ft_free(&split, 'a'), 1))
		exit_failure(cub, ELEMENTS_SPACE_ERR);
	if (!ft_strrchr(split[1], '.xpm'))
		return (ft_free(&split, 'a'), exit_failure(cub, ELEMENTS_IMG_NAME_ERR));
	txtr->img = mlx_xpm_file_to_image(cub->mlx_ptr, split[1], &width, &height);
	ft_free(&split, 'a');
	if (!txtr->img)
		exit_failure(cub, ELEMENTS_IMG_CORRUPTED_ERR);
	txtr->height = height;
	txtr->width = width;
	txtr->addr = mlx_get_map_addr(txtr->img,
			&txtr->bpp, &txtr->line_len, &txtr->endian);
}

static void	validate_color(t_cub *cub, int *arr, int *value, char *line)
{
	int	colors_counter;
	int	commas_counter;
	int	letters_counter;

	colors_counter = 0;
	commas_counter = 0;
	letters_counter = 0;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		line += ft_iscomma(*line, &commas_counter);
		if (commas_counter > colors_counter)
			exit_failure(cub, COLOR_ERR);
		line += ft_isletter(*line, &letters_counter);
		line += is_color(cub, line, &colors_counter, arr);
		if (colors_counter == 3 && commas_counter != 2)
			exit_failure(cub, COLOR_ERR);
		if (letters_counter > 1 || commas_counter > 2 || colors_counter > 3)
			exit_failure(cub, COLOR_ERR);
	}
	if (*value != -1 || letters_counter != 1
		|| commas_counter != 2 || colors_counter != 3)
		exit_failure(cub, COLOR_ERR);
	*value = create_rgb(arr);
}

static void	validate_elements(t_cub *cub, char *line)
{
	t_file		*file;
	t_txtrs		*txtrs;
	size_t		len;

	file = &cub->file;
	txtrs = cub->txtrs;
	len = ft_strlen(line);
	if (ft_strnstr(line, "NO", len))
		validate_img(cub, txtrs->no, line);
	else if (ft_strnstr(line, "SO", len))
		validate_img(cub, txtrs->so, line);
	else if (ft_strnstr(line, "WE", len))
		validate_img(cub, txtrs->we, line);
	else if (ft_strnstr(line, "EA", len))
		validate_img(cub, txtrs->ea, line);
	else if (ft_strnstr(line, "F", len))
		validate_color(cub, txtrs->f_arr, &txtrs->f_color, line);
	else if (ft_strnstr(line, "C", len))
		validate_color(cub, txtrs->c_arr, &txtrs->c_color, line);
	if (is_textures_ready(cub->txtrs))
		file->stage++;
}

static void	validate_map(t_cub *cub, t_file *file, t_map *map, int st)
{
	int	is_empty_line_exist;

	is_empty_line_exist = 0;
	if (!map->map_st || !map->map_end)
		exit_failure(cub, MAP_EMPTY_ERR);
	map->map_height = map->map_end - map->map_st;
	if (map->map_height < 3)
		exit_failure(cub, MAP_HEIGHT_ERR);
	while (st <= map->map_end && file->file_arr[st])
	{
		set_map_width(map, file->file_arr[st]);
		is_player(cub, file->file_arr[st], st - map->map_st);
		is_empty_line_exist += ft_isempty_str(file->file_arr[st]);
		map->wall_counter += ft_iswall(file->file_arr[st]);
		if (map->plyr_counter && !map->wall_counter)
			exit_failure(cub, MAP_WALL_ERR);
		else if (is_empty_line_exist && ft_ismap_line(file->file_arr[st]))
			exit_failure(cub, MAP_EMPTY_LINE);
		st++;
	}
	if (map->plyr_counter != 1)
		exit_failure(cub, MAP_CHARS_ERR);
	if (map->wall_counter < 2)
		exit_failure(cub, MAP_WALL_ERR);
}

/*
	*	file_validate(t_cub *cub, t_file *file)
	{
			- This function is used to validate the file.
		- It has 2 while loops:
			-	One for the element portion of the file.
			-	The other for the map portion of the file.
		- There's 2 stages here, 1 for elements and 2 for the map.

		It has 4 sections:
			1- Elements while loop (Stage 1)
				- It has 3 conditions:
					-	Empty line => i++.
					-	Element line => parse it and validate it.
					-	Not Empty and not element line while the stage still 1
						=> exit error.
					-	Once we got all our elements ready and accepted 
						=> increment the stage to stage 2 (the map stage).
			2- Map while loop (Stage 2)
				- It has 3 conditions:
					-	Empty line => i++.
					-	if (!file->map_st) We didn't set the starting index 
						of the map && NOT Element line (means a map line)
						=> set the map start index and i++.
					-	else if not empty line and not a map line just break out.
			3- Set the map end index.
			4- Validate the map
	}

	*	validate_elements(t_cub *cub, t_file *file, char *line)
	{
		- This function is used to validate the elements portion of the file.
		- It has 5 conditions:
			1-	NO => validate the image path.
			2-	SO => validate the image path.
			3-	WE => validate the image path.
			4-	EA => validate the image path.
			5-	F or C => validate the color.
			Once we got all the elements ready, we increment the stage to 2.
		- While we are validating the colors we increment the is_valid_colors
		  counter, it's a flag we use to check if we got our colors ready or not,
		  if there's was an error while validating the colors,
		  we will exist anyway, so we won't reach the limit where we check,
		  if our elements are ready or not, if there was no error,
		  then we simply did an early increment,
		  the conclusion is it's a well calculated and we are good.
	}

	*	validate_img(t_cub *cub, t_txtdata *txtr, void **img, char *line)
	{
		- This function is used to validate 3 things:
			1- If the image is not already set.
			2- If the image extention is valid.
			3- If the image is not corrupted.
			
		- It has 4 sections:
			1-	If the image is already set => exit error.
				i.e passing the same element twice on the map
			2-	Split the line by a whitespace.
				-	If it splits into more than 2 parts => exit error.
					i.e. the line should be like "NO ./path/to/img.xpm"
					but not like "NO ./path/to/img.xpm 100 100"
				- 	So if NOT split[0] || NOT split[1] || split[2] 
					=> exit error.
			3-	If the image extention is not .xpm => exit error.
			4-	Set the img to whatever mlx_xpm_file_to_image returns.
			Return the img and save into it's variable.
	}

	*	validate_color(t_cub *cub, int *arr, char *line)
	{
		- This function is used to validate the color.
		- It takes the arr based on what color we are validating.
		- It has 2 sections:
			1-	While loop:
				-	IF it was whitespace => increment the line.
				-	If i's a comma => increment the commas counter & the line.
				-	If i's a letter => increment the letters counter & the line.
				-	If it's a color => increment the color counter & the line.
				-	If (letters > 1 || commas > 2 || colors > 3)
					=> exit error.
				-	We are only allowing 1 Letter and we are sure that 
					this letter will be either F or C (check validate_elements).
				-	We are only allowing 2 commas.
				-	We are only allowing 3 colors.
			2-	If Condition:
				-	If the letters counter is not 1 => exit error.
					i.e. FF or F 10T,10,10
				-	If the commas counter is not 2 => exit error.
					i.e. F 10,10 10
				-	If the color_idx is not 3 => exit error.
					i.e. F 10,10
	}
	
	*	validate_map(t_cub *cub, t_file *file, int st)
	{
		- This function is used to validate the map in these aspects:
			-	Count the letters and if they are a player ot not.
			-	Validate the empty lines within & after the map,
				and check if it's valid to create or not, if not => early exit.
			-	After this function we are sure that we have 1 player, 2 or
				more walls and the map is valid for creation,
				(there's no empty lines within the map).
			-	We didn't yet check if the map it self is valid or not.
			-	We will do that after we create the map.
		- It has 4 sections:
			1-	If map start index or end index == 0 => exit error.
			2-	If map length < 3 => exit error.
			3-	While loop:
				-	Set the map width and keep updating it to get the max width.
				-	Check if it's a player or not.
					- If it's a player => increment the player counter.
					- If not exist error.
				-	We have a flag for empty lines within the map,
					if it's found or not.
				-	We sat a counter for walls, and we keep trace of it.
				-	If we found a player and no walls => exit error.
				-	If we found an empty line within the map => exit error.
					-	If our is_empty_line_exist has a value, 
						meaning we found empty line,
						now if the current line we are at is a map line,
						=> exit error.
						i.e:
							1111
							1101

							11N1
							1111
			-	If the player counter != 1 => exit error.
			-	If the wall counter < 2 => exit error.
				There's no problem if we had multiple walls.
	}
*/
