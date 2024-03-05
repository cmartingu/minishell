/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:02:09 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/26 17:02:11 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	if (!*lst)
		*lst = new;
	else
	{
		aux = *lst;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}
/*int main(void)
{
	t_list	begin;
	
	begin = NULL;
    ft_lstadd_back(&begin, elem);
    ft_lstadd_back(&begin, elem2);
    ft_lstadd_back(&begin, elem3);
    ft_lstadd_back(&begin, elem4);
    while (begin)
    {
        ft_print_result(begin);
        begin = begin->next;
    }
	return (0);
}*/