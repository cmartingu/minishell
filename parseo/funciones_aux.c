/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funciones_lib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:21:29 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:21:32 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_process_back(t_process *proceso, t_process *proceso2)
{
	t_process	*aux_process;

	aux_process = proceso;
	while (aux_process->next != NULL)
		aux_process = aux_process->next;
	aux_process->next = proceso2;
}

void	ft_realloc_doble(t_process *proceso, char *str, int tam)
{
	char	**final_cmd;

	final_cmd = malloc((tam + 1) * sizeof(char *));
	if (!final_cmd)
	{
		printf("Error, malloc error");
		exit(1);
	}
	final_cmd[tam] = NULL;
	final_cmd[tam - 1] = ft_strdup(str);
	tam--;
	while (tam--)
		final_cmd[tam] = ft_strdup((proceso->command)[tam]);
	free_arr(&(proceso->command));
	proceso->command = final_cmd;
}
