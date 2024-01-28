/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:53:13 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/19 23:53:14 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*sol;
	int		i;

	i = 0;
	sol = malloc(ft_strlen(s) + 1);
	if (!sol)
		return (0);
	sol[ft_strlen(s)] = '\0';
	while (s[i])
	{
		sol[i] = f(i, (char)s[i]);
		i++;
	}
	return (sol);
}
