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

void	no_quot_tam_aux(char *cmd, int *i, int *quant, char **copy_env)
{
	if (cmd[*i] == '$')
		(*quant) -= add_expansion(cmd, i, copy_env);
	else if (cmd[*i] == '\'')
	{
		(*i)++;
		(*quant) += 2;
		while (cmd[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	else if (cmd[*i] == '"')
	{
		(*i)++;
		(*quant) += 2;
		while (cmd[*i] != '"')
		{
			if (cmd[*i] == '$')
				(*quant) -= add_expansion(cmd, i, copy_env);
			else
				(*i)++;
		}
		(*i)++;
	}
	else
		(*i)++;
}

int	no_quot_tam(char *cmd, char **copy_env)
{
	int	i;
	int	quant;

	i = 0;
	quant = 0;
	while (cmd[i] != '\0')
	{
		no_quot_tam_aux(cmd, &i, &quant, copy_env);
	}
	return (i - quant);
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

void	command_quot(char *cmd, char **final, char **copy_env)
{
	t_auxiliar	*aux;

	aux = malloc(sizeof(t_auxiliar));
	aux->j = 0;
	aux->i = 0;
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
