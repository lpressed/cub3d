/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_sc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 19:26:34 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/29 02:12:44 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	len_file(char *line)
{
	int n;

	n = 0;
	while (*line != ' ' && *line != '\0' && *line != '\n')
	{
		n++;
		line++;
	}
	return (n);
}

static char	*skip_sim(char *line)
{
	while (*line != ',' && *line != '\0' && *line != '\n')
		line++;
	if (*line == ',')
		line++;
	else
		return (NULL);
	return (line);
}

int			is_filename(char *line, char **filename)
{
	int n;

	while (*line != '\0' && *line == ' ' && *line != '\n')
		line++;
	n = len_file(line);
	if (n == 0)
		return (-1);
	*filename = (char*)malloc((n + 1) * sizeof(char));
	if (*filename == NULL)
		return (-1);
	ft_strlcpy(*filename, line, n + 1);
	while (*line != '\0' && *line != ' ' && *line != '\n')
		line++;
	while (*line != '\0' && *line == ' ' && *line != '\n')
		line++;
	if (*line != '\0' && *line != '\n')
		return (-1);
	return (1);
}

int			is_rgb(char *line, int *red, int *green, int *blue)
{
	*red = ft_atoi(line);
	if (*red < 0 || *red > 255)
		return (-1);
	if (!(line = skip_sim(line)))
		return (-1);
	*green = ft_atoi(line);
	if (*green < 0 || *green > 255)
		return (-1);
	if (!(line = skip_sim(line)))
		return (-1);
	*blue = ft_atoi(line);
	if (*blue < 0 || *blue > 255)
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

int			join_line(t_map *map, char *line)
{
	char	*buf;

	buf = map->map_buf;
	map->map_buf = ft_strjoin(map->map_buf, line);
	if (map->map_buf == NULL)
	{
		free(buf);
		return (-1);
	}
	buf = map->map_buf;
	map->map_buf = ft_strjoin(map->map_buf, "\n");
	if (map->map_buf == NULL)
	{
		free(buf);
		return (-1);
	}
	return (1);
}
