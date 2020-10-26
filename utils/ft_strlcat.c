/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student21.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 00:44:20 by lpressed          #+#    #+#             */
/*   Updated: 2020/05/05 01:06:14 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_src;
	size_t	size_dst;

	size_dst = (size_t)dst;
	size_src = ft_strlen(src);
	while (*dst != '\0' && size != 0)
	{
		dst++;
		size--;
	}
	size_dst = (size_t)dst - size_dst;
	if (size == 0)
		return (size_src + size_dst);
	while (size - 1 > 0 && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		size--;
	}
	*dst = '\0';
	return (size_src + size_dst);
}
