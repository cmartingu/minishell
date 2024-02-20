/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funciones_lib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:21:29 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:21:32 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*sol;

	len = ft_strlen(s1);
	sol = malloc(len + 1);
	if (!sol)
		return (0);
	sol[len] = '\0';
	while (len--)
		sol[len] = s1[len];
	return (sol);
}

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
