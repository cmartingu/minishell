/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:23:32 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 14:23:34 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*auxh;
	size_t	i;
	size_t	j;

	i = 0;
	auxh = (char *)haystack;
	if (*needle == '\0')
		return ((char *) haystack);
	while ((i < len) && (haystack[i]))
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			auxh = (char *)&haystack[i];
			while (haystack[i] == needle[j] && (needle[j] != '\0'))
			{
				i++;
				j++;
			}
			if (needle[j] == '\0' && (i <= len))
				return (auxh);
		}
		i = i - j + 1;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char a[] = "hola que tal?";
	char b[] = "que";
	printf("%s\n", ft_strnstr(a, b, 9));
	printf("%s", strnstr(a, b, 9));
	return (0);
}*/