/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:50:18 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 18:50:21 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char s1[] = "hola";
	char *s2;
	char *s3;
	s2 = ft_strdup(s1);
	s3 = strdup(s1);
	printf("%s\n%s", s2, s3);
	free(s2);
	free(s3);
	return (0);
}*/