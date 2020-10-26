/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_valid_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:17:48 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/30 01:00:18 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			check_pos(t_map *map, int x, int y)
{
	if (map->n_map >= y && map->w_map[y] >= x)
	{
		if (map->map_form[y][x] == ' ' || map->map_form[y][x] == '\0')
			error(map, 1);
		if (map->map_form[y][x] == '1' || map->map_form[y][x] == '.' ||
			map->map_form[y][x] == 's' || map->map_form[y][x] == 'd')
			return (1);
		if (map->map_form[y][x] == '0')
			map->map_form[y][x] = '.';
		if (map->map_form[y][x] == '2')
		{
			map->n_sprite++;
			map->map_form[y][x] = 's';
		}
		if (ft_strchr("NSWE", map->map_form[y][x]))
			map->map_form[y][x] = 'd';
		check_pos(map, x + 1, y);
		check_pos(map, x - 1, y);
		check_pos(map, x, y + 1);
		check_pos(map, x, y - 1);
		return (1);
	}
	else
		error(map, 1);
	return (-1);
}

static int	find_pos(t_map *map)
{
	int x;
	int	y;

	y = 0;
	while (map->map_form[y] != 0)
	{
		x = 0;
		while (map->map_form[y][x] != '\0')
		{
			if (ft_strchr("EWSN", map->map_form[y][x]))
			{
				map->start_pos_x = x;
				map->start_pos_y = y;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int			get_xy_sprite(t_map *map)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (map->map_form[i] != 0)
	{
		j = 0;
		while (map->map_form[i][j] != '\0')
		{
			if (map->map_form[i][j] == 's')
			{
				map->x_sprite[n] = j;
				map->y_sprite[n] = i;
				n++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int			cub_valid_map(t_map *map)
{
	find_pos(map);
	if (check_pos(map, map->start_pos_x, map->start_pos_y) == -1)
	{
		free_map_form(map, map->n_map);
		free_map_filename(map);
		return (-1);
	}
	return (1);
}

int			free_map_buf(t_map *map)
{
	if (map->map_buf != NULL)
		free(map->map_buf);
	return (-1);
}
