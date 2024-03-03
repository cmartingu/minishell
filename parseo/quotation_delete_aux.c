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

int	enviroment_sustitution(char *name_var, char **copyEnv)
{
    char *final_str;
    int i = 0;
    int name_len;

	final_str = NULL;
    name_len = ft_strlen(name_var);
    while (copyEnv[i] != NULL)
	{
        if (strncmp(name_var, copyEnv[i], name_len) == 0 && copyEnv[i][name_len] == '=')
		{
            final_str = strdup(copyEnv[i] + name_len + 1);
            break;
        }
        i++;
    }

    return (ft_strlen(final_str));
}


int	add_expansion(char *cmd, int *i, char **copyEnv)
{
	char	*name_var;
	int		aux;
	int		quit_chars;
	int		j;

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
	j = 0;
	while (j < quit_chars)
	{
		(*i)++;
		j++;
	}
	return (enviroment_sustitution(name_var, copyEnv) - quit_chars);
}

int	no_quot_tam(char *cmd, char **copyEnv)
{
	int	i;
	int	quant;
	int	auxiliar;

	i = 0;
	quant = 0;
	auxiliar = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$')//Añadir expansion
			auxiliar += add_expansion(cmd, &i, copyEnv);
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
					auxiliar += add_expansion(cmd, &i, copyEnv);
				else
					i++;
			}
		}
		i++;
	}
	return (i - quant + auxiliar);
}

void	save_expansion(char **aux, int *j, char **copyEnv, char *name_var)
{
	char *final_str;
    int i = 0;
    int name_len;

	final_str = NULL;
    name_len = ft_strlen(name_var);
    while (copyEnv[i] != NULL)
	{
        if (strncmp(name_var, copyEnv[i], name_len) == 0 && copyEnv[i][name_len] == '=')
		{
            final_str = strdup(copyEnv[i] + name_len + 1);
            break;
        }
        i++;
    }
	if (copyEnv[i] == NULL)
		return ;
	i = 0;
	while (final_str[i] != '\0')
	{
		(*aux)[*j] = final_str[i];
		(*j)++;
		i++;
	}
}

void	expansion_print(char **aux, int *i, int *j, char *cmd, char **copyEnv)
{
	char	*name_var;
	int		auxiliar;
	int		quit_chars;
	int		k;

	(*i)++;
	auxiliar = *i;
	while (cmd[*i] != '\0' && cmd[*i] != '"' && cmd[*i] != ' ' && cmd[*i] != '$')
		(*i)++;
	auxiliar = (*i) - auxiliar;
	name_var = malloc((auxiliar + 1));
	name_var[auxiliar] = '\0';
	(*i)--;
	quit_chars = auxiliar + 1;//los caracteres que hay que quitar($HOLA, habría que quitar 5)
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
	save_expansion(aux, j, copyEnv, name_var);
	//return (enviroment_sustitution(name_var, copyEnv) - quit_chars);
}

void	command_quot(char *cmd, char **aux, int *i, int *j, char **copyEnv)
{
	if (cmd[*i] == '$')
		expansion_print(aux, i, j, cmd, copyEnv);
	if (cmd[*i] == '"')
	{
		(*i)++;
		while (cmd[*i] != '"')
		{
			if (cmd[*i] == '$')
				expansion_print(aux, i, j, cmd, copyEnv);
			else
			{
				(*aux)[*j] = cmd[*i];
				(*i)++;
				(*j)++;
			}
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

char	*final_command(char *cmd, int tam, char **copyEnv)
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
		command_quot(cmd, &aux, &i, &j, copyEnv);//Meter el bucle en la funcion e iicializar dentro i y j para poder pasar env
		i++;
	}
	return (aux);
}