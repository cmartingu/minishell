/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:36:11 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/13 18:08:18 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*sol;
	unsigned const char	*copiar;

	sol = (unsigned char *)dst;
	copiar = (unsigned char *)src;
	if (!copiar && !sol)
		return (0);
	while (n > 0)
	{
		*sol = *copiar;
		sol++;
		copiar++;
		n--;
	}
	return (dst);
}

/*int main(void)
{
	char b[20] = "";
	char a[10] = "";
	ft_memcpy(b, a, 3);
	printf("%s", b);
	return (0);
}*/