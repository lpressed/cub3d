/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:18:19 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/29 02:08:12 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		is_r(char *line, t_map *map)
{
	map->width = ft_atoi(line);
	if (map->width <= 0)
		return (-1);
	while (*line == ' ' && *line != '\0' && *line != '\n')
		line++;
	while (ft_isdigit(*line) && *line != '\0' && *line != '\n')
		line++;
	map->heigth = ft_atoi(line);
	if (map->heigth <= 0)
		return (-1);
	while (*line == ' ' && *line != '\0' && *line != '\n')
		line++;
	while (ft_isdigit(*line) && *line != '\0' && *line != '\n')
		line++;
	while (*line == ' ' && *line != '\0' && *line != '\n')
		line++;
	if (*line != '\0' && *line != '\n')
		return (-1);
	return (1);
}

static int		is_str2(char *line, t_map *map)
{
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (is_filename(line + 3, &(map->no)));
	if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (is_filename(line + 3, &(map->so)));
	if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		return (is_filename(line + 3, &(map->we)));
	if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		return (is_filename(line + 3, &(map->ea)));
	if (*line != '\0' && *line != '\n')
		return (-1);
	return (0);
}

static int		is_str(char *line, t_map *map)
{
	while (*line == ' ' && !ft_strchr("\n\0", *line))
		line++;
	if (!ft_strchr("\n\0", *line) && !ft_strchr("\n\0", *(line + 1)))
	{
		if (*line == 'R' && *(line + 1) == ' ')
			return (is_r(line + 2, map));
		if (*line == 'S' && *(line + 1) == ' ')
			return (is_filename(line + 2, &(map->s)));
		if (*line == 'F' && *(line + 1) == ' ')
		{
			return (is_rgb(line + 2, &(map->f_red),
						&(map->f_green), &(map->f_blue)));
		}
		if (*line == 'C' && *(line + 1) == ' ')
		{
			return (is_rgb(line + 2, &(map->c_red),
						&(map->c_green), &(map->c_blue)));
		}
		if (!ft_strchr("\n\0", *(line + 2)))
			return (is_str2(line, map));
	}
	if (*line != '\0' && *line != '\n')
		return (-1);
	return (0);
}

static int		proc_line(char *line, t_map *map)
{
	int	ch;
	int	ch1;

	if (map->sum < 8)
	{
		if ((ch = is_str(line, map)) == -1)
			return (-1);
		if (ch == 1)
		{
			map->sum += 1;
			return (1);
		}
	}
	else
	{
		if ((ch1 = check_line(map, line)) == -1)
			return (free_map_buf(map));
		if (((ch1 == 0) || check_spaces(line)) && map->sum == 8)
			return (0);
		map->sum += 1;
		return (join_line(map, line));
	}
	return (1);
}

int				cub_parse(t_map *map, char *file)
{
	int		ch;
	char	*line;

	ch = open(file, O_RDONLY);
	if (ch == -1)
		return (-1);
	line = NULL;
	while (get_next_line(ch, &line) > 0)
	{
		if (proc_line(line, map) == -1)
		{
			free(line);
			get_next_line(-1, &line);
			return (free_map_filename(map));
		}
		free(line);
	}
	if (proc_line(line, map) == -1 || map->position == '0')
	{
		free(line);
		get_next_line(-1, &line);
		return (free_map_filename(map));
	}
	free(line);
	return (map_parse(map));
}
