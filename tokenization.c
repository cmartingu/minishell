#include "minishell.h"

void	quant_aux(char **cmd, int *quant, int *i)
{
	if (((*cmd)[*i] == '<' && (*cmd)[(*i) + 1] == '<') || \
	((*cmd)[(*i)] == '>' && (*cmd)[(*i) + 1] == '>'))
	{
		(*quant)++;
		(*i)++;
		(*i)++;
		if ((*cmd)[*i] != ' ' && (*cmd)[*i] != '\0' && \
		(*cmd)[*i] != '|' && (*cmd)[*i] != '<' && (*cmd)[*i] != '>')
			(*quant)++;
	}
	else if ((*cmd)[*i] == '|' || (*cmd)[*i] == '<' || (*cmd)[*i] == '>')
	{
		(*quant)++;
		(*i)++;
		if ((*cmd)[*i] != ' ' && (*cmd)[*i] != '\0' && (*cmd)[*i] != '|' \
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
		while (cmd[i] != ' ' && cmd[i] != '\0')
			quant_aux(&cmd, &quant, &i);
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
	while ((*cmd)[i] != '<' && (*cmd)[i] != '>' && (*cmd)[i] != '|' && \
	(*cmd)[i] != ' ' && (*cmd)[i] != '\0')
		i++;
	if (i == 0)
		return (NULL);
	aux_tkn = malloc(i + 1);
	aux_tkn[i] = '\0';
	skip_tam = i;
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