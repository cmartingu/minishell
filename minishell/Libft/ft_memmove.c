/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:09:07 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/13 19:12:53 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*sol;
	unsigned const char	*copiar;

	sol = (unsigned char *)dst;
	copiar = (unsigned char *)src;
	if (!copiar && !sol)
		return (0);
	if (src > dst)
	{
		while (len > 0)
		{
			*sol = *copiar;
			sol++;
			copiar++;
			len--;
		}
		return (dst);
	}
	while (len--)
		sol[len] = copiar[len];
	return (dst);
}

/*#include <stdio.h>
int main(void)
{
	char b[10] = "hola como";
	char a[20] = "paco va mal hola";
	ft_memmove(b, a, 0);
	printf("%s", b);
	return (0);
}*/
