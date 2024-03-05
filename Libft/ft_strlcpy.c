/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:14:01 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/13 19:43:40 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	cont;
	int		contsrc;

	cont = 0;
	contsrc = 0;
	while (src[contsrc])
		contsrc++;
	if (dstsize == 0)
		return (contsrc);
	while ((cont < (dstsize - 1)) && (*src))
	{
		*dst = *src;
		dst++;
		src++;
		cont++;
	}
	*dst = '\0';
	return (contsrc);
}

/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char a[20];
	char b[] = "Hola, mundo!";

	size_t res = ft_strlcpy(a, b, 10);
	printf("%s\n%zu", a, res);
	return (0);
}*/
