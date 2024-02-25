/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:19:06 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:19:07 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quotation(char **cmd, int *i)
{
	(*i)++;
	while ((*cmd)[*i] != '"')
		(*i)++;
	(*i)++;
}

void	quant_aux(char **cmd, int *quant, int *i)
{
	if ((*cmd)[*i] == '"')
		count_quotation(cmd, &*i);
	else if (((*cmd)[*i] == '<' && (*cmd)[(*i) + 1] == '<') || \
	((*cmd)[(*i)] == '>' && (*cmd)[(*i) + 1] == '>'))
	{
		(*quant)++;
		(*i)++;
		(*i)++;
		if ((*cmd)[*i] == '"')
		{
			(*quant)++;
			return ;
		}
		if ((*cmd)[*i] != ' ' && (*cmd)[*i] != '\0' && \
		(*cmd)[*i] != '|' && (*cmd)[*i] != '<' && (*cmd)[*i] != '>')
			(*quant)++;
	}
	else if ((*cmd)[*i] == '|' || (*cmd)[*i] == '<' || (*cmd)[*i] == '>')
	{
		(*quant)++;
		(*i)++;
		if ((*cmd)[*i] == '"')
		{
			(*quant)++;
			return ;
		}
		if ((*cmd)[*i] != '\0' && (*cmd)[*i] != ' ' && (*cmd)[*i] != '|' \
		&& (*cmd)[*i] != '<' && (*cmd)[*i] != '>')
		{
			(*quant)++;
			(*i)++;
		}
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
		{
			i++;
			while (cmd[i] != '"')
				i++;
			i++;
		}
		else
		{
			while (cmd[i] != ' ' && cmd[i] != '\0')
				quant_aux(&cmd, &quant, &i);
		}
	}
	return (quant);
}

char	*save_word_case(char **cmd)
{
	int		i;
	char	*aux_tkn;
	int		skip_tam;

	i = 0;
	if ((*cmd)[i] == '|')
	{
		(*cmd)++;
		return (strdup("|"));
	}
	while ((*cmd)[i] != '\0' && (*cmd)[i] != ' ' && (*cmd)[i] != '|' && (*cmd)[i] != '<' && (*cmd)[i] != '>')
	{
		if ((*cmd)[i] == '"')
			count_quotation(cmd, &i);
		else
			i++;
	}
	skip_tam = i;
	aux_tkn = malloc(i + 1);
	aux_tkn[i] = '\0';
	while (i--)
		aux_tkn[i] = (*cmd)[i];
	while (skip_tam-- > 0)
		(*cmd)++;
	return (aux_tkn);
}

char	*next_token(char **cmd)
{
	int		i;

	i = 0;
	if ((*cmd)[i] == '>')
	{
		(*cmd)++;
		if ((*cmd)[i] == '>')
		{
			(*cmd)++;
			return (strdup(">>"));
		}
		return (strdup(">"));
	}
	else if ((*cmd)[i] == '<')
	{
		(*cmd)++;
		if ((*cmd)[i] == '<')
		{
			(*cmd)++;
			return (strdup("<<"));
		}
		return (strdup("<"));
	}
	return (save_word_case(cmd));
}

char	**save_tokens(int tam, char **cmd)
{
	char	**tokens;
	char	*aux_cmd;
	int		j;

	j = 0;
	aux_cmd = (*cmd);
	tokens = malloc((tam + 1) * sizeof(char *));
	if (!tokens)
	{
		write(2, "Error, malloc error\n", 20);
		exit(1);
	}
	while (**cmd != '\0')
	{
		while (*(*cmd) == ' ')
			(*cmd)++;
		if (*(*cmd) != '\0')
		{
			tokens[j] = next_token(cmd);
			j++;
		}
	}
	(*cmd) = aux_cmd;
	tokens[j] = NULL;
	return (tokens);
}
