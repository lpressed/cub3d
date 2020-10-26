/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student21.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:59:02 by lpressed          #+#    #+#             */
/*   Updated: 2020/05/05 19:36:52 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
		i++;
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
		j++;
	dst = (char*)malloc((i + j + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		ft_strlcpy(dst, s1, i + 1);
		free(s1);
	}
	else
		dst[0] = '\0';
	if (s2 != NULL)
		ft_strlcat(dst, s2, i + j + 1);
	return (dst);
}
