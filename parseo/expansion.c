/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:33:26 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 13:33:27 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (quit_chars--)
		(*i)++;
	save_expansion(aux, j, copy_env, name_var);
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
