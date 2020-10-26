/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student21.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 00:19:01 by lpressed          #+#    #+#             */
/*   Updated: 2020/05/16 12:30:13 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	size_src;

	size_src = ft_strlen(src);
	if (size == 0)
		return (size_src);
	while (size - 1 > 0 && *src)
	{
		*dst = (char)*src;
		dst++;
		src++;
		size--;
	}
	if (size - 1 == 0 || !*src)
		*dst = '\0';
	return (size_src);
}
