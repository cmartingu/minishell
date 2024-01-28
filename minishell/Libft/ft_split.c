/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:00:02 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/17 13:00:04 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cpal(char const *s, char c)
{
	int	palabras;

	palabras = 0;
	if (*s && (*s != c))
		palabras++;
	while (*s)
	{
		if ((*s == c) && (*(s +1) != c) && (*(s + 1) != '\0'))
			palabras++;
		s++;
	}
	return (palabras);
}

char	*annadir(char const *s, int tampal)
{
	char	*aux;
	int		j;

	j = 0;
	aux = malloc(tampal + 1);
	if (!aux)
		return (0);
	aux[tampal] = '\0';
	j = 0;
	while (j < tampal)
	{
		*aux = *s;
		s++;
		aux++;
		j++;
	}
	aux -= tampal;
	return (aux);
}

void	rm_all(char **sol, int i)
{
	while (i >= 0)
	{
		free(sol[i]);
		i--;
	}
	free(sol);
}

int	hacer(const char *s, char c, int i, char **sol)
{
	int	tampal;

	tampal = 0;
	while (*s && (*s != c))
	{
		tampal++;
		s++;
	}
	s -= tampal;
	sol[i] = annadir(s, tampal);
	if (!sol[i])
	{
		rm_all(sol, i);
		return (0);
	}
	return (tampal);
}

char	**ft_split(char const *s, char c)
{
	char	**sol;
	int		tampal;
	int		i;

	while (*s == c && *s != '\0')
		s++;
	sol = malloc(((cpal(s, c)) + 1) * sizeof(char *));
	if (!sol)
		return (0);
	i = 0;
	while (*s)
	{
		tampal = hacer(s, c, i, sol);
		if (tampal == 0)
			return (0);
		s += tampal;
		while (*s == c && *s)
			s++;
		i++;
	}
	sol[i] = NULL;
	return (sol);
}
/*#include <stdio.h>
int main(void)
{
	char s[] = "\0aa\0bbb";
	char **fin;
	fin = ft_split(s, '\0');
	while (*fin)
	{
		printf("%s\n", *fin);
		fin++;
	}
	free(*fin);
	fin--;
	free(*fin);
//	fin--;
//	free(*fin);
	free(fin);
	return (0);
}*/