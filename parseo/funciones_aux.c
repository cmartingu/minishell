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

int	gramatical_errors(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (tokens[i + 1] == NULL || tokens[i + 1][0] == '<' || tokens[i + 1][0] == '>' \
			|| tokens[i + 1][0] == '|')
			{
				free_array(tokens);
				return (-1);
			}
		}
		if (tokens[i][0] == '|')
		{
			if (tokens[i + 1] == NULL || tokens[i + 1][0] == '|')
			{
				free_array(tokens);
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

t_process	*tokenization_string(char *cmd, char **copy_env)
{
	t_process	*process;
	t_process	*aux_process;
	char		**tokens;
	int			tam;
	int			forks;

	if (contador_comillas(cmd) == -1)
	{
		printf("Minishell error: Acuerdate de cerrar las comillas\n");
		exit(1);
	}
	tam = token_quant(cmd);
	if (tam == 0)
		return (NULL);
	tokens = save_tokens(tam, &cmd);
	if (gramatical_errors(tokens) == -1)
		return (NULL);
	forks = pipes_quant(tokens) + 1;
	process = procesos(forks, tokens);
	aux_process = process;
	while (aux_process != NULL)
	{
		delete_all_quot(aux_process, copy_env);
		aux_process = aux_process->next;
	}
	return (process);
}

int	count_process(t_process *procesos)
{
	t_process	*aux;
	int			i;

	aux = procesos;
	i = 0;
	while (aux != NULL)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}
