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
				i++;
		}
		i++;
	}
	return (i - quant);
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
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] != '"')
			{
				aux[j] = cmd[i];
				i++;
				j++;
			}
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				aux[j] = cmd[i];
				i++;
				j++;
			}
		}
		else
		{
			aux[j] = cmd[i];
			j++;
		}
		i++;
	}
	return (aux);
}

char	*delete_quotation(char **cmd)
{
	char	*aux_cmd;
	int		tam;

	if (has_quot(*cmd) == -1)
	{
		aux_cmd = ft_strdup(*cmd);
		free(*cmd);
		return (aux_cmd);
	}
	tam = no_quot_tam(*cmd);
	aux_cmd = final_command(*cmd, tam);
	printf("FINAL STR: %s\n", aux_cmd);
	return (NULL);
}