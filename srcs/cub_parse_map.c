/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 13:39:11 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/29 00:46:31 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	strlen_n(char *str)
{
	int n;

	n = 0;
	while (*str != '\n' && *str != '\0')
	{
		n++;
		str++;
	}
	return (n);
}

int			check_line(t_map *map, char *line)
{
	if (line == NULL)
		return (-1);
	if (*line == '\0' || *line == '\n')
		return (0);
	while (*line != '\n' && *line != '\0')
	{
		if (!ft_strchr("NESW120 ", *line))
			return (-1);
		if (ft_strchr("NESW", *line) && map->position == '0')
			map->position = *line;
		else if (ft_strchr("NESW", *line) && map->position != '0')
			return (-1);
		line++;
	}
	return (1);
}

int			check_spaces(char *line)
{
	if (line == NULL)
		return (-1);
	while (*line != '\n' && *line != '\0')
	{
		if (*line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int			convert_buf(t_map *map, int n)
{
	int		m;
	int		b;
	char	**buf_form;

	if ((map->map_form = (char**)malloc((n + 2) * sizeof(char*))) == NULL)
		return (-1);
	buf_form = map->map_form;
	b = n;
	while (n >= 0)
	{
		m = strlen_n(map->map_buf) + 1;
		if ((*(map->map_form) = (char*)malloc((m + 1) * sizeof(char))) == NULL)
		{
			map->map_form = buf_form;
			free_map_form(map, b - n);
			return (-1);
		}
		ft_strlcpy(*(map->map_form), map->map_buf, m);
		map->map_buf = map->map_buf + m;
		map->map_form++;
		n--;
	}
	*(map->map_form) = 0;
	map->map_form = buf_form;
	return (1);
}

int			map_parse(t_map *map)
{
	char	*start_buf;

	start_buf = map->map_buf;
	while (*(map->map_buf) != '\0')
	{
		map->map_buf++;
		if (*(map->map_buf) == '\n')
			map->n_map++;
	}
	map->map_buf = start_buf;
	if (convert_buf(map, map->n_map) == -1)
	{
		free(start_buf);
		return (free_map_filename(map));
	}
	free(start_buf);
	if (calc_map_w(map) == -1)
	{
		free_map_form(map, map->n_map);
		return (free_map_filename(map));
	}
	return (1);
}
