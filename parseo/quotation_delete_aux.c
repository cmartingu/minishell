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

int	enviroment_sustitution(char *name_var, char **copy_env, \
int *iter, int cant_iter)
{
	char	*final_str;
	int		i;
	int		name_len;
	int		j;

	i = 0;
	final_str = NULL;
	name_len = ft_strlen(name_var);
	while (copy_env[i] != NULL)
	{
		if (strncmp(name_var, copy_env[i], name_len) == 0 && \
		copy_env[i][name_len] == '=')
		{
			final_str = strdup(copy_env[i] + name_len + 1);
			break ;
		}
		i++;
	}
	j = 0;
	while (j < cant_iter)
	{
		(*iter)++;
		j++;
	}
	return (ft_strlen(final_str));
}

int	add_expansion(char *cmd, int *i, char **copy_env)
{
	char	*name_var;
	int		aux;
	int		quit_chars;

	(*i)++;
	aux = *i;
	while (cmd[*i] != '\0' && cmd[*i] != '"' && cmd[*i] != ' ' \
	&& cmd[*i] != '$')
		(*i)++;
	aux = (*i) - aux;
	name_var = malloc((aux + 1));
	name_var[aux] = '\0';
	(*i)--;
	quit_chars = aux + 1;
	while (aux--)
	{
		name_var[aux] = cmd[*i];
		(*i)--;
	}
	return (enviroment_sustitution(name_var, copy_env, i, \
	quit_chars) - quit_chars);
}

void	no_quot_tam_aux(char *cmd, int *i, int *quant, char **copy_env)
{
	if (cmd[*i] == '$')
		quant -= add_expansion(cmd, i, copy_env);
	if (cmd[*i] == '\'')
	{
		(*i)++;
		(*quant) += 2;
		while (cmd[*i] != '\'')
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
	}
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
		i++;
	}
	return (i - quant);
}

void	save_expansion(char **aux, int *j, char **copy_env, char *name_var)
{
	char	*final_str;
	int		i;
	int		len;

	i = 0;
	final_str = NULL;
	len = ft_strlen(name_var);
	while (copy_env[i] != NULL)
	{
		if (strncmp(name_var, copy_env[i], len) == 0 && copy_env[i][len] == '=')
		{
			final_str = strdup(copy_env[i] + len + 1);
			break ;
		}
		i++;
	}
	if (copy_env[i] == NULL)
		return ;
	i = 0;
	while (final_str[i] != '\0')
	{
		(*aux)[*j] = final_str[i];
		(*j)++;
		i++;
	}
}

void	expansion_print(char **aux, int *i, int *j, char *cmd, char **copy_env)
{
	char	*name_var;
	int		auxiliar;
	int		quit_chars;
	int		k;

	(*i)++;
	auxiliar = *i;
	while (cmd[*i] != '\0' && cmd[*i] != '"' && \
	cmd[*i] != ' ' && cmd[*i] != '$')
		(*i)++;
	auxiliar = (*i) - auxiliar;
	name_var = malloc((auxiliar + 1));
	name_var[auxiliar] = '\0';
	(*i)--;
	quit_chars = auxiliar + 1;
	while (auxiliar--)
	{
		name_var[auxiliar] = cmd[*i];
		(*i)--;
	}
	k = 0;
	while (k < quit_chars)
	{
		(*i)++;
		k++;
	}
	save_expansion(aux, j, copy_env, name_var);
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
				{
					(*aux)[j] = cmd[i];
					i++;
					j++;
				}
			}
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				(*aux)[j] = cmd[i];
				i++;
				j++;
			}
		}
		else
		{
			(*aux)[j] = cmd[i];
			j++;
		}
		i++;
	}
}

char	*final_command(char *cmd, int tam, char **copy_env)
{
	char	*aux;

	aux = malloc(tam + 1);
	if (!aux)
	{
		printf("Minishell error: malloc error\n");
		exit(1);
	}
	aux[tam] = '\0';
	command_quot(cmd, &aux, copy_env);
	return (aux);
}
