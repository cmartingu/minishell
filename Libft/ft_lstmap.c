/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:29:52 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/26 17:29:53 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*sol;
	t_list	*aux;
	t_list	*auxfin;
	void	*cont;

	aux = lst;
	sol = 0;
	auxfin = sol;
	while (aux)
	{
		cont = f(aux->content);
		sol = ft_lstnew(cont);
		if (!sol)
		{
			del(cont);
			ft_lstclear(&auxfin, del);
			return (0);
		}
		ft_lstadd_back(&auxfin, sol);
		aux = aux->next;
	}
	return (auxfin);
}
