/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:58:19 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 12:58:21 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*aux1;
	unsigned char	*aux2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	aux1 = (unsigned char *) s1;
	aux2 = (unsigned char *) s2;
	while ((i < (n - 1)) && (aux1[i] == aux2[i]))
		i++;
	return (aux1[i] - aux2[i]);
}
/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char s1[] = "\0";
	char s2[] = "\0hola que tal";
	printf("%d\n", ft_memcmp(s1, s2, sizeof(s2)));
	printf("%d", memcmp(s1, s2, sizeof(s2)));
	return (0);
}*/