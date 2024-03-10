/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:17:01 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 11:17:02 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_unset(char **coman, char ***copyenv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (coman[i] != NULL)
	{
		j = 0;
		while ((*copyenv)[j] != NULL)
		{
			if (ft_strncmp((*copyenv)[j], coman[i], ft_strlen(coman[i])) == 0 &&
			(*copyenv)[j][ft_strlen(coman[i])] == '=')
			{
				while ((*copyenv)[j] != NULL)
				{
					(*copyenv)[j] = (*copyenv)[j + 1];
					j++;
				}
				break ;
			}
			j++;
		}
		i++;
	}
}
