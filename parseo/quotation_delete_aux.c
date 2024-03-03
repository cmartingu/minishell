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

#include "minishell.h"

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

char	*enviroment_sustitution(char *name_var, char **env)
{
	char	*final_str;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(name_var, env[i], ft_strlen(name_var)))
		i++;
	if (env[i] == NULL)
		return (NULL);
	final_str = ft_strdup(env[i] + ft_strlen(name_var) + 1);
	printf("%s\n", final_str);
}

int	add_expansion(char *cmd, int *i, char **env)
{
	char	*name_var;
	int		aux;
	int		quit_chars;

	(*i)++;
	aux = *i;
	while (cmd[*i] != '\0' && cmd[*i] != '"' && cmd[*i] != ' ' && cmd[*i] != '$')
		(*i)++;
	aux = (*i) - aux;
	name_var = malloc((aux + 1));
	name_var[aux] = '\0';
	(*i)--;
	quit_chars = aux + 1;//los caracteres que hay que quitar($HOLA, habría que quitar 5)
	while (aux--)
	{
		name_var[aux] = cmd[*i];
		(*i)--;
	}
	printf("%s\n", name_var);
	return (0);
}

int	no_quot_tam(char *cmd)
{
	int	i;
	int	quant;

	i = 0;
	quant = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'')
		{
			i++;
			quant += 2;
			while (cmd[i] != '\'')
				i++;
		}
		else if (cmd[i] == '"')
		{
			i++;
			quant += 2;
			while (cmd[i] != '"')
			{
				if (cmd[i] == '$')//Añadir expansion
				{
				}
				i++;
			}
		}
		i++;
	}
	return (i - quant);
}

void	command_quot(char *cmd, char **aux, int *i, int *j)
{
	if (cmd[*i] == '"')
	{
		(*i)++;
		while (cmd[*i] != '"')
		{
			(*aux)[*j] = cmd[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (cmd[*i] == '\'')
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

char	*final_command(char *cmd, int tam)
{
	char	*aux;
	int		i;
	int		j;

	aux = malloc(tam + 1);
	if (!aux)
	{
		printf("Minishell error: malloc error\n");
		exit(1);
	}
	aux[tam] = '\0';
	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		command_quot(cmd, &aux, &i, &j);
		i++;
	}
	return (aux);
}