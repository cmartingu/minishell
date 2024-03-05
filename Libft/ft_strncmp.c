/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:43:50 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 11:43:53 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*aux1;
	unsigned char	*aux2;

	aux1 = (unsigned char *)s1;
	aux2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((aux1[i] == aux2[i]) && (i < (n - 1)))
	{
		if (aux1[i] == '\0' && aux2[i] == '\0')
			return (0);
		i++;
	}
	return (aux1[i] - aux2[i]);
}

/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char s1[] = "\0hola";
	char s2[] = "\0paco";
	printf("%d", strncmp(s1, s2, 5));
	return (0);
}*/