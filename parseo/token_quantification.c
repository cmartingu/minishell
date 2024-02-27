/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quantification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:45:04 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/27 15:45:06 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quotation(char **cmd, int *i, char quot)
{
	(*i)++;
	while ((*cmd)[*i] != quot)
		(*i)++;
	(*i)++;
}

void	char_exc(char **cmd, int *quant, int *i)
{
	if ((*cmd)[*i] == '"' || (*cmd)[*i] == '\'')
	{
		(*quant)++;
		return ;
	}
	if ((*cmd)[*i] != ' ' && (*cmd)[*i] != '\0' && \
	(*cmd)[*i] != '|' && (*cmd)[*i] != '<' && (*cmd)[*i] != '>')
	{
		(*quant)++;
		(*i)++;
	}
}

void	quant_aux(char **cmd, int *quant, int *i)
{
	if ((*cmd)[*i] == '"')
		count_quotation(cmd, i, '"');
	else if ((*cmd)[*i] == '\'')
		count_quotation(cmd, i, '\'');
	else if (((*cmd)[*i] == '<' && (*cmd)[(*i) + 1] == '<') || \
	((*cmd)[(*i)] == '>' && (*cmd)[(*i) + 1] == '>'))
	{
		(*quant)++;
		(*i)++;
		(*i)++;
		char_exc(cmd, quant, i);
	}
	else if ((*cmd)[*i] == '|' || (*cmd)[*i] == '<' || (*cmd)[*i] == '>')
	{
		(*quant)++;
		(*i)++;
		char_exc(cmd, quant, i);
	}
	else
		(*i)++;
}

int	token_quant(char *cmd)
{
	int		i;
	int		quant;

	quant = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] != '\0' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
			quant++;
		if (cmd[i] == '"')
			count_quotation(&cmd, &i, '"');
		if (cmd[i] == '\'')
			count_quotation(&cmd, &i, '\'');
		else
		{
			while (cmd[i] != ' ' && cmd[i] != '\0')
				quant_aux(&cmd, &quant, &i);
		}
	}
	return (quant);
}