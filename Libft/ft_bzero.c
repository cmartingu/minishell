/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:27:00 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/13 17:35:30 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*sol;

	sol = s;
	while (n > 0)
	{
		*sol = (unsigned char) 0;
		sol++;
		n--;
	}
}

/*int main(void)
{
	char b[20] = "hola que tal";
	ft_bzero(b, 4);
	printf("%s", b);
	return (0);
}*/
