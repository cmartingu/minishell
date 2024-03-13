/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:01:20 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/26 13:01:21 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_quot(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			return (0);
		i++;
	}
	return (-1);
}

void	no_quot_tam_aux(char *cmd, t_auxiliar *aux, char **copy_env, int stats)
{
	if (cmd[aux->i] == '$')
		(aux->status) -= add_expansion(cmd, &(aux->i), copy_env, stats);
	else if (cmd[aux->i] == '\'')
	{
		(aux->i)++;
		(aux->status) += 2;
		while (cmd[aux->i] != '\'')
			(aux->i)++;
		(aux->i)++;
	}
	else if (cmd[aux->i] == '"')
	{
		(aux->i)++;
		(aux->status) += 2;
		while (cmd[aux->i] != '"')
		{
			if (cmd[aux->i] == '$')
				(aux->status) -= add_expansion(cmd, &(aux->i), copy_env, stats);
			else
				(aux->i)++;
		}
		(aux->i)++;
	}
	else
		(aux->i)++;
}

int	no_quot_tam(char *cmd, char **copy_env, int stats)
{
	t_auxiliar	*aux;
	int			p;

	aux = malloc(sizeof(t_auxiliar));
	aux->i = 0;
	aux->status = 0;
	while (cmd[aux->i] != '\0')
		no_quot_tam_aux(cmd, aux, copy_env, stats);
	p = (aux->i) - (aux->status);
	free(aux);
	return (p);
}

void	aux_command_quot(char *cmd, int *i, int *j, char **aux)
{
	if (cmd[*i] == '\'')
	{
		(*i)++;
		while (cmd[*i] != '\'')
		{
			(*aux)[*j] = cmd[*i];
			(*i)++;
			(*j)++;
		}
	}
	else
	{
		(*aux)[*j] = cmd[*i];
		(*j)++;
	}
}

void	command_quot(char *cmd, char **final, char **copy_env, int status)
{
	t_auxiliar	*aux;

	aux = ini_aux(status);
	while (cmd[aux->i] != '\0')
	{
		if (cmd[aux->i] == '$')
			expansion_print(cmd, aux, final, copy_env);
		if (cmd[aux->i] == '"')
		{
			(aux->i)++;
			while (cmd[aux->i] != '"')
			{
				if (cmd[aux->i] == '$')
					expansion_print(cmd, aux, final, copy_env);
				else
					save_final_quot(final, cmd, &(aux->i), &(aux->j));
			}
		}
		else
			aux_command_quot(cmd, &(aux->i), &(aux->j), final);
		(aux->i)++;
	}
	free(aux);
}
