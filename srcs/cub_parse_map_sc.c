/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map_sc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:13:59 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/29 01:51:04 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	free_map_form(t_map *map, int n)
{
	char	**form_buf;

	form_buf = map->map_form;
	while (n >= 0)
	{
		free(*(map->map_form));
		n--;
		map->map_form++;
	}
	free(form_buf);
	free(map->w_map);
	return (1);
}

int	free_map_filename(t_map *map)
{
	if (map->no != NULL)
		free(map->no);
	if (map->s != NULL)
		free(map->s);
	if (map->so != NULL)
		free(map->so);
	if (map->we != NULL)
		free(map->we);
	if (map->ea != NULL)
		free(map->ea);
	return (-1);
}

int	calc_map_w(t_map *map)
{
	char	**start_map_form;
	int		*start_w_map;
	int		n;

	map->w_map = (int*)malloc((map->n_map) * sizeof(int));
	if (map->w_map == NULL)
		return (-1);
	start_w_map = map->w_map;
	start_map_form = map->map_form;
	n = map->n_map;
	while (n > 0)
	{
		*(map->w_map) = ft_strlen(*(map->map_form));
		map->map_form++;
		map->w_map++;
		n--;
	}
	map->w_map = start_w_map;
	map->map_form = start_map_form;
	return (1);
}
