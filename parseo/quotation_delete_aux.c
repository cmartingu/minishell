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
