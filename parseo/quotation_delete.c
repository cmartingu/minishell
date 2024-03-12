/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:13:57 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/27 16:14:00 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	end_quotation(char **cmd, char quot)
{
	(*cmd)++;
	while ((**cmd) != '\0' && (**cmd) != quot)
		(*cmd)++;
	if ((**cmd) == quot)
		return (0);
	return (-1);
}

int	contador_comillas(char *comando)
{
	char	*aux_cmd;

	if (!comando)
		return (-1);
	aux_cmd = comando;
	while (*comando != '\0')
	{
		if (*comando == '"')
		{
			if (end_quotation(&comando, '"') == -1)
				return (-1);
		}
		else if (*comando == '\'')
		{
			if (end_quotation(&comando, '\'') == -1)
				return (-1);
		}
		comando++;
	}
	comando = aux_cmd;
	return (0);
}

char	*final_command(char *cmd, int tam, char **copy_env, int status)
{
	char	*aux;

	aux = malloc(tam + 1);
	if (!aux)
	{
		printf("Minishell error: malloc error\n");
		exit(1);
	}
	aux[tam] = '\0';
	command_quot(cmd, &aux, copy_env, status);
	return (aux);
}

void	delete_quotation(char **cmd, char **copy_env, int status)
{
	char	*aux_cmd;
	int		tam;

	if (!cmd)
		return ;
	tam = no_quot_tam(*cmd, copy_env, status);
	aux_cmd = final_command(*cmd, tam, copy_env, status);
	free(*cmd);
	(*cmd) = aux_cmd;
}

void	delete_all_quot(t_process *process, char **copy_env, int status)
{
	t_fileobject	*aux_file;
	char			**aux_command;

	aux_file = process->infile;
	while (aux_file != NULL)
	{
		delete_quotation(&(aux_file->filename), copy_env, status);
		aux_file = aux_file->next;
	}
	aux_file = process->outfile;
	while (aux_file != NULL)
	{
		delete_quotation(&(aux_file->filename), copy_env, status);
		aux_file = aux_file->next;
	}
	aux_command = process->command;
	if (aux_command)
	{
		while ((*aux_command) != NULL)
		{
			delete_quotation(aux_command, copy_env, status);
			aux_command++;
		}
	}
}
