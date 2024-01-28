/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:26:22 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 12:26:28 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sol;

	sol = (unsigned char *)s;
	while ((n > 0))
	{
		if (*sol == (unsigned char) c)
			return (sol);
		sol++;
		n--;
	}
	return ((unsigned char *) 0);
}
/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[] = "hola cque tal, como vas?";
	printf("%s\n", ft_memchr(s, 'd', sizeof(s)));
	printf("%s", memchr(s, 'd', sizeof(s)));
	return (0);
}*/