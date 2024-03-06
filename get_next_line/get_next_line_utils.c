/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:45:43 by carlos-m          #+#    #+#             */
/*   Updated: 2023/11/29 11:45:45 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*sol;
	size_t			i;

	i = 0;
	sol = malloc(count * size);
	if (!sol)
		return (0);
	while (i < (count * size))
	{
		sol[i] = (unsigned char) 0;
		i++;
	}
	return (sol);
}

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*sol;

	len = ft_strlen(s1);
	sol = malloc(len + 1);
	if (!sol)
		return (NULL);
	sol[len] = '\0';
	while (len--)
		sol[len] = s1[len];
	return (sol);
}

char	*ft_realloc(char *aux, int tam, char c)
{
	char	*sol;
	int		i;
	char	*aux_aux;

	if (!aux)
		aux = ft_strdup(" ");
	aux_aux = aux;
	tam++;
	sol = malloc(tam + 1);
	if (!sol)
		return (NULL);
	sol[tam] = '\0';
	i = 0;
	while (i < (tam - 1) && *aux)
	{
		sol[i] = *aux;
		aux++;
		i++;
	}
	free(aux_aux);
	sol[tam - 1] = c;
	return (sol);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
