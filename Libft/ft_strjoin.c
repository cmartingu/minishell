/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:29 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/16 16:25:30 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	tam;
	char	*sol;
	char	*aux;

	tam = ft_strlen(s1) + ft_strlen(s2);
	sol = malloc(tam + 1);
	if (!sol)
		return (0);
	aux = sol;
	while (*s1)
	{
		*aux = *s1;
		aux++;
		s1++;
	}
	while (*s2)
	{
		*aux = *s2;
		aux++;
		s2++;
	}
	*aux = '\0';
	return (sol);
}

/*#include <stdio.h>
int main(void)
{
	char s1[] = "hola que tal";
	char s2[] = ", como estas?";
	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/