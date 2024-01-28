/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:41:03 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/16 16:41:05 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_coincide(char s, const char *set)
{
	while (*set)
	{
		if (s == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*buscar1(char const *s1, char const *set)
{
	int		encontrado;
	char	*aux1;

	encontrado = 0;
	while (*s1 && (encontrado == 0))
	{
		if (ft_coincide(*s1, set) == 0)
		{
			encontrado = 1;
			aux1 = (char *)s1;
			return (aux1);
		}
		if (encontrado == 0)
			s1++;
	}
	return ((char *)s1);
}

static char	*buscar2(char const *s1, char const *set, char *aux1)
{
	int		encontrado;
	char	*aux2;

	encontrado = 0;
	while ((s1 >= aux1) && (encontrado == 0))
	{
		if (ft_coincide(*s1, set) == 0)
		{
			encontrado = 1;
			aux2 = (char *)s1;
			return (aux2);
		}
		if (encontrado == 0)
			s1--;
	}
	return (0);
}

static int	tam(const char *aux1, const char *aux2)
{
	int	len;

	len = 0;
	while (aux1 <= aux2)
	{
		aux1++;
		len++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*aux1;
	char	*aux2;
	char	*sol;

	aux1 = buscar1(s1, set);
	if (*aux1 == '\0')
		return (ft_strdup(""));
	while (*s1)
		s1++;
	s1--;
	aux2 = buscar2(s1, set, aux1);
	len = tam(aux1, aux2);
	sol = malloc(len + 1);
	if (!sol)
		return (0);
	sol[len] = '\0';
	while (len--)
	{
		sol[len] = *aux2;
		aux2--;
	}
	return (sol);
}
/*#include <stdio.h>
int main(void)
{
	char s1[] = "jujuholajuholajuju";
	char set[] = "ju";
	printf("%s", ft_strtrim(s1, set));
	return (0);
}*/ 