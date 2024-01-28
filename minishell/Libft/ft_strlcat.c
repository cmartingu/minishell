/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:37:24 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/13 20:28:48 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*aux;
	size_t	cont;
	size_t	ret;

	cont = 0;
	aux = dst;
	if (dstsize == 0)
		return (ft_strlen(src));
	ret = ft_strlen(dst) + ft_strlen(src);
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while ((*dst != '\0') && (cont < dstsize))
	{
		cont++;
		dst++;
	}
	while ((*src != '\0') && (cont++ < (dstsize - 1)))
		*dst++ = *src++;
	*dst = '\0';
	dst = aux;
	return (ret);
}

/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char a[40] = "hola que tal";
	char b[] = ", como estás?";
	size_t tam = strlcat(a, b, 0);
	printf("%s\n%zu", a, tam);
	return (0);
}*/