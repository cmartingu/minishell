/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:39:28 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 11:39:57 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	tam;

	tam = ft_strlen(s);
	while (tam >= 0)
	{
		if (s[tam] == (char) c)
			return ((char *)&s[tam]);
		tam--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[] = "hola,como cccestas?";
	char c = 'c';
	printf("%s\n", ft_strrchr(s, c));
	printf("%s", s);
	return (0);
}*/
