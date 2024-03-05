/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:29:26 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/14 18:29:28 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*#include <stdio.h>
int main(void)
{
	int i = 0;
	int f = 0;
	int *n = ft_calloc(6, sizeof(int));
	int *d = calloc(6, sizeof(int));
	while (i < 6)
	{
		printf("%d ", n[i]);
		i++;
	}
	printf("\n");
	while (f < 6)
	{
		printf("%d ", d[f]);
		f++;
	}
	return (0);
}*/