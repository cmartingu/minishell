/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:14:03 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/16 12:14:05 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sol;
	size_t	i;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	i = 0;
	sol = malloc(len + 1);
	if (!sol)
		return (0);
	sol[len] = '\0';
	while (len--)
		sol[len] = s[start + len];
	return (sol);
}

/*#include <stdio.h>
int main(void)
{
	char s[] = "hola q";
	printf("%s", ft_substr(s, 5, 4));
	return (0);
}*/