/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student21.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:25:40 by lpressed          #+#    #+#             */
/*   Updated: 2020/05/02 18:48:52 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_int(int nb, int nptr)
{
	if (nb > 0 && (nb > (2147483647 / 10) || nb > (2147483647 - nptr)))
		return (-1);
	if (nb < 0 && (nb < (-2147483647 / 10) || nb < (-2147483647 - nptr)))
		return (-1);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n' ||
			nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (check_int(nb, nptr[i] - 48) == -1)
			return (-1);
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb * sign);
}
