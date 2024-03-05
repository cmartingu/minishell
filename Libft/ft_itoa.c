/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:50:45 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/19 20:50:47 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ndigitos(long int n, int signo)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	if (signo == -1)
		return (i + 1);
	return (i);
}

char	*ft_hacer(int signo, int ndig, long int n)
{
	char	*sol;

	if (n == 0)
		return (ft_strdup("0"));
	if (signo == -1)
	{
		sol = malloc(ndig + 1);
		if (!sol)
			return (0);
		sol[ndig] = '\0';
		sol[0] = '-';
	}
	else
	{
		sol = malloc(ndig + 1);
		if (!sol)
			return (0);
		sol[ndig] = '\0';
	}
	return (sol);
}

char	*ft_itoa(int n)
{
	char		*sol;
	int			signo;
	int			ndig;
	long int	nb;

	nb = n;
	signo = 1;
	if (nb < 0)
	{
		signo = -1;
		nb *= -1;
	}
	ndig = ndigitos(nb, signo);
	sol = ft_hacer(signo, ndig, nb);
	if (!sol)
		return (0);
	while (ndig--)
	{
		if (nb > 0)
			sol[ndig] = (char){(nb % 10) + '0'};
		nb = nb / 10;
	}
	return (sol);
}
/*#include <stdio.h>
int main(void)
{
	printf("%s", ft_itoa(0));
	return (0);
}*/