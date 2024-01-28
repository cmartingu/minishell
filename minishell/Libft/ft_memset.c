/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:22:08 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/13 17:26:26 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*sol;

	sol = b;
	while (len > 0)
	{
		*sol = (unsigned char)c;
		sol++;
		len--;
	}
	return (b);
}

/*int main(void)
{
	char b[20] = "hola que tal";
	ft_memset(b, 'c', 4);
	printf("%s", b);
	return (0);
}*/
