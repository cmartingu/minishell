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

void	command_quot(char *cmd, char **aux, char **copy_env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$')
			expansion_print(aux, &i, &j, cmd, copy_env);
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] != '"')
			{
				if (cmd[i] == '$')
					expansion_print(aux, &i, &j, cmd, copy_env);
				else
					save_final_quot(aux, cmd, &i, &j);
			}
		}
		else
			aux_command_quot(cmd, &i, &j, aux);
		i++;
	}
}
