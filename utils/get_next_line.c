/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:06:44 by lpressed          #+#    #+#             */
/*   Updated: 2020/07/06 16:44:49 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	free_memory(char **line, char **stmp, int type_free)
{
	if (type_free == 0)
	{
		free(*line);
		if (*stmp != NULL)
		{
			free(*stmp);
			*stmp = NULL;
		}
	}
	if (type_free == 2 && *stmp != NULL)
	{
		free(*stmp);
		*stmp = NULL;
	}
	return (-1);
}

static int	static_buf_proc(char **line, char **static_buf, char **stmp)
{
	char *tmp;

	if ((tmp = ft_strchr(*static_buf, '\n')))
	{
		*tmp = '\0';
		if ((*line = ft_strjoin(*line, *static_buf)) == NULL)
			return (-1);
		tmp++;
		*static_buf = tmp;
		return (1);
	}
	else
	{
		if ((*line = ft_strjoin(*line, *static_buf)) == NULL)
			return (-1);
		free_memory(NULL, &(*stmp), 2);
		*static_buf = NULL;
		return (2);
	}
}

static int	read_fd(int fd, char **line, char **static_buf, char **stmp)
{
	int		check_rd;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	while ((check_rd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[check_rd] = '\0';
		if ((tmp = ft_strchr(buf, '\n')))
		{
			*tmp = '\0';
			if ((*line = ft_strjoin(*line, buf)) == NULL)
				return (-1);
			tmp++;
			if ((*static_buf = ft_strdup(tmp)) == NULL)
				return (-1);
			*stmp = *static_buf;
			return (1);
		}
		if ((*line = ft_strjoin(*line, buf)) == NULL)
			return (-1);
	}
	if (check_rd == -1)
		return (-1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*static_buf = NULL;
	static char *stmp;
	int			ret;
	int			r;

	ret = 0;
	if (BUFFER_SIZE < 1 || fd < 0 || line == NULL)
		return (free_memory(line, &stmp, 2));
	if (*line != NULL)
		*line = NULL;
	*line = ft_strdup("");
	if (*line == NULL)
		return (free_memory(NULL, &stmp, 2));
	if (static_buf != NULL)
		ret = static_buf_proc(&(*line), &static_buf, &stmp);
	if (ret == -1)
		return (free_memory(&(*line), &stmp, 0));
	if (ret == 2 || static_buf == NULL)
	{
		if ((r = read_fd(fd, &(*line), &static_buf, &stmp)) == -1 || ret == -1)
			return (free_memory(&(*line), &stmp, 0));
		return (r);
	}
	return (ret);
}
