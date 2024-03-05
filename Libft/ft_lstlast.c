/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:29:42 by carlos-m          #+#    #+#             */
/*   Updated: 2023/09/26 14:29:44 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*sol;

	sol = lst;
	if (sol == NULL)
		return (NULL);
	while (sol->next != NULL)
	{
		sol = sol->next;
	}
	return (sol);
}
