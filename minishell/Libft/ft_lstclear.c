/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:20:44 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/26 17:20:46 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;
	t_list	*aux2;

	aux2 = *lst;
	if (!aux2 || !lst)
		return ;
	while (aux2)
	{
		aux = aux2->next;
		del(aux2->content);
		free(aux2);
		aux2 = aux;
	}
	*lst = NULL;
}
