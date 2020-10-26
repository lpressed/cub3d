/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student21.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:24:50 by lpressed          #+#    #+#             */
/*   Updated: 2020/05/07 21:54:57 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_b;
	unsigned char	*s2_b;

	if (n == 0 || (s1 == NULL && s2 == NULL))
		return (0);
	s1_b = (unsigned char*)s1;
	s2_b = (unsigned char*)s2;
	while (n > 0 && *s1_b && *s2_b)
	{
		if (*s1_b > *s2_b)
			return (1);
		else if (*s1_b++ < *s2_b++)
			return (-1);
		else
			n--;
	}
	if (*s1_b == '\0' && *s2_b != '\0' && n != 0)
		return (-1);
	if (*s2_b == '\0' && *s1_b != '\0' && n != 0)
		return (1);
	return (0);
}
