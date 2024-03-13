/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:20:35 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/13 14:20:36 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_status(t_auxiliar *aux, char **final)
{
	char	*stat;
	int		aux_iter;

	(aux->i)++;
	stat = ft_itoa(aux->status);
	aux_iter = 0;
	while (stat[aux_iter] != '\0')
	{
		(*final)[aux->j] = stat[aux_iter];
		aux_iter++;
		(aux->j)++;
	}
	free(stat);
}

int	question_tam(int status, int *i)
{
	int	j;

	j = 1;
	(*i)++;
	while (status >= 10)
	{
		j++;
		status = status / 10;
	}
	return (j);
}

t_auxiliar	*ini_aux(int status)
{
	t_auxiliar	*aux;

	aux = malloc(sizeof(t_auxiliar));
	aux->j = 0;
	aux->i = 0;
	aux->status = status;
	return (aux);
}
