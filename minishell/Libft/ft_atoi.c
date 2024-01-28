/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:35:24 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 15:35:27 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	signo;
	int	nb;

	signo = 1;
	nb = 0;
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if (*str == '-')
	{
		str++;
		signo = -1;
	}
	else if (*str == '+')
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{
		nb = (nb * 10) + (int){*str - '0'};
		str++;
	}
	return (nb * signo);
}
/*#include <stdio.h>
int main(void)
{
	printf("%d\n%d", ft_atoi("-123a"), atoi("-123a"));
	return (0);
}*/