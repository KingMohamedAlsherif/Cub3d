/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:23:56 by dehamad           #+#    #+#             */
/*   Updated: 2024/08/31 16:15:05 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	file_len(t_cub *cub, char *input_file);
static void	file_create(t_cub *cub, t_file *file, char *input_file);
static void	map_create(t_cub *cub, t_map *map, int st, int end);
static void	map_validate(t_cub *cub, t_map *map, char **map_arr, char invalid);

void	parsing(t_cub *cub, char *input_file)
{
	t_file	*file;
	t_map	*map;
	int		len;

	file = &cub->file;
	map = cub->map;
	len = cub->file.filepath_len;
	if ((len - 4) <= 0 || ft_strcmp(".cub", input_file + (len - 4)))
		exit_failure(cub, INVALID_FILE_NAME);
	file_len(cub, input_file);
	file_create(cub, file, input_file);
	file_validate(cub, file, cub->map);
	map_create(cub, map, map->map_st, map->map_end);
	map_validate(cub, map, map->map_arr, '\0');
}

static void	file_len(t_cub *cub, char *input_file)
{
	int		fd;
	t_gnl	ret;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		exit_failure(cub, INVALID_FD);
	while (fd >= 0)
	{
		ret = ft_get_next_line(fd);
		if (ret.error)
			return ((void)close(fd), exit_failure(cub, READ_ERR));
		if (!ret.line)
			break ;
		ft_free(&ret.line, 'p');
		cub->file.file_len++;
	}
	close(fd);
	if (!cub->file.file_len)
		exit_failure(cub, INVALID_FILE_EMPTY);
	if (cub->file.file_len < 9)
		exit_failure(cub, INVALID_FILE_NOT_COMPLETE);
}

static void	file_create(t_cub *cub, t_file *file, char *input_file)
{
	int		fd;
	int		idx;
	t_gnl	ret;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		exit_failure(cub, INVALID_FD);
	file->file_arr = (char **)ft_calloc(file->file_len + 1, sizeof(char *));
	if (!file->file_arr)
		exit_failure(cub, MALLOC_ERR);
	idx = 0;
	while (fd >= 0)
	{
		ret = ft_get_next_line(fd);
		if (ret.error)
			return ((void)close(fd), exit_failure(cub, READ_ERR));
		if (!ret.line)
			break ;
		if (ft_istab(ret.line))
			exit_failure(cub, TAB_ERR);
		file->file_arr[idx++] = ret.line;
	}
	close(fd);
}

static void	map_create(t_cub *cub, t_map *map, int st, int end)
{
	char	**file_arr;
	int		idx;

	file_arr = cub->file.file_arr;
	map->map_arr = ft_calloc(map->map_height + 1, sizeof(char *));
	if (!map->map_arr)
		exit_failure(cub, MALLOC_ERR);
	idx = 0;
	while (st <= end && file_arr[st] && *file_arr[st])
	{
		if (ft_isempty_str(file_arr[st]) && ++st)
			continue ;
		map->map_arr[idx] = set_map_line(cub, map, file_arr[st]);
		if (!map->map_arr[idx])
			exit_failure(cub, MALLOC_ERR);
		st++;
		idx++;
	}
	map->map_height = idx;
	if (map->map_height < 3)
		exit_failure(cub, MAP_HEIGHT_ERR);
	if (!ft_iswall(map->map_arr[0]) || !ft_iswall(map->map_arr[idx - 1]))
		exit_failure(cub, MAP_WALL_ERR);
}

static void	map_validate(t_cub *cub, t_map *map, char **map_arr, char invalid)
{
	int	y;
	int	x;

	y = -1;
	while (map_arr[++y])
	{
		x = -1;
		while (map_arr[y][++x])
		{
			if (map_arr[y][x] == ' ')
				invalid = '0';
			else if (map_arr[y][x] == map->plyr_direction)
				invalid = ' ';
			else
				continue ;
			if (x > 0 && map_arr[y][x - 1] == invalid)
				return (exit_failure(cub, MAP_SPACE_ERR));
			if (x < map->map_width - 1 && map_arr[y][x + 1] == invalid)
				return (exit_failure(cub, MAP_SPACE_ERR));
			if (y > 0 && map_arr[y - 1][x] == invalid)
				return (exit_failure(cub, MAP_SPACE_ERR));
			if (y < map->map_height - 1 && map_arr[y + 1][x] == invalid)
				return (exit_failure(cub, MAP_SPACE_ERR));
		}
	}
}

/*
	*	parsing(t_cub *cub, char *input_file)
	{
		- check if the file name is valid
		- we get the length of the file name (check init.c)
		- we check if there's a name given prior to the .cub extension
		- we check if the file name does not end with .cub
		- if the file name is invalid we exit with INVALID_FILE_NAME	
	}

	*	file_len(t_cub *cub, char *input_file)
	{
		- used to get the length of the file
		- we open the file we make sure we have a valid fd
		- we read the file line by line and increment the file_len 
		- if (!ret.line) returned NULL == no malloc, so we break
		- we close the file
		- if the file_len is 0 we exit with INVALID_FILE_NAME
	}

	*	file_create(t_cub *cub, t_file *file, char *input_file));
	{
		- read the file and store it in file_arr
		- we open the file we make sure we have a valid fd
		- we malloc based on the file_len from the previous function
		- we read the file line by line and store it in file_arr
		- if (!ret.line) returned NULL == no malloc, so we break
		- we close the file
	}

	*	file_validate(t_cub *cub, t_file *file, t_map *map);
	{
		-	validate the whole file (elements and map)
		-	in this function we fully validate the elements
		-	yet we dob't validate the map,
			we only check if it's valid for creation or not
	}

	*	map_create(t_cub *cub, t_file *file, t_map *map);
	{
		-	create the map
		-	we malloc the map based on the map_height
		-	we skip the empty lines
		-	we set the map line
			(so that all lines are equal in length, we fill with spaces)
		-	if the map line is NULL we exit with MALLOC_ERR
		-	we increment the st and idx
		-	we set the new map_end
		-	we set the map_height
		-	if the new map_height 
			then we check if it's less than 3 we exit with MAP_HEIGHT_ERR
		-	we will need the new map height in the next function (map_validate)
	}

	*	map_validate(t_cub *cub, t_map *map, char **map_arr, char invalid);
	{
		-	validate the map
		-	we check if the map is surrounded by walls
		-	if we found space we always check the surrounding, 
			if we will go with the traditional way,
			we have to check multiple cases:
				i.e y = 0 or y = map_height - 1 or in between
			and at each one of them there's multiple cases:
				i.e x = 0 or x = map_width - 1 or in between
			we have to do that so for example:
				if it was y = 0 we don't want to check the upper line
				if it was y = map_height - 1 we don't want to check the next line
				same goes with x and that's lots of checking
			to avoid that we will check the opposite scenarios:
				i.e:
				we don't want to check the left side of x = 0
					so if (x > 0 && map[y][x - 1] == invalid)
				we don't want to check the right side of x = map_width - 1
					so if (x < file->map_width - 1 && map[y][x + 1] == invalid)
				we don't want to check the upper side of y = 0
					so if (y > 0 && map[y - 1][x] == invalid)
				we don't want to check the lower side of y = map_height - 1
					so if (y < file->map_height - 1 && map[y + 1][x] == invalid)
				this way we avoid the invalid checks and we check everything else
				if any of these condition end up invalid we exit with err
	}
*/
