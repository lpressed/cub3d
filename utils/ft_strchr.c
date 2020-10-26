/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student21.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 01:11:32 by lpressed          #+#    #+#             */
/*   Updated: 2020/05/03 13:00:59 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_buf;

	s_buf = (char*)s;
	while (*s_buf)
	{
		if (*s_buf == c)
			return (s_buf);
		s_buf++;
	}
	if (c == '\0' && *s_buf == '\0')
		return (s_buf);
	return (NULL);
}
