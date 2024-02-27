/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:11:29 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/22 15:11:30 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes_quant(char **tokens)
{
	int		pipes;
	int		i;

	i = 0;
	pipes = 0;
	while (tokens[i] != NULL)
	{
		if (*(tokens[i]) == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

void	add_infile(t_process *proceso, char *inf)
{
	t_fileobject	*new_file;
	t_fileobject	*aux_file;

	new_file = malloc(sizeof(new_file));
	if (!new_file)
	{
		printf("Error, malloc error\n");
		exit(1);
	}
	new_file->filename = ft_strdup(inf);
	new_file->next = NULL;
	if (!(proceso->infile))
		proceso->infile = new_file;
	else
	{
		aux_file = proceso->infile;
		while (aux_file->next != NULL)
			aux_file = aux_file->next;
		aux_file->next = new_file;
	}
}

void	add_outfile(t_process *proceso, char *outf)
{
	t_fileobject	*new_file;
	t_fileobject	*aux_file;

	new_file = malloc(sizeof(new_file));
	if (!new_file)
	{
		printf("Error, malloc error\n");
		exit(1);
	}
	new_file->filename = ft_strdup(outf);
	new_file->next = NULL;
	if (!(proceso->outfile))
		proceso->outfile = new_file;
	else
	{
		aux_file = proceso->outfile;
		while (aux_file->next != NULL)
			aux_file = aux_file->next;
		aux_file->next = new_file;
	}
}

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
}

void	add_cmd(t_process *proceso, char *cmd, int cmd_quant)
{
	if (!(proceso->command))
	{
		proceso->command = malloc(2 * sizeof(char *));
		if (!(proceso->command))
		{
			printf("Error, malloc error");
			exit(1);
		}
		(proceso->command)[0] = ft_strdup(cmd);
		(proceso->command)[1] = NULL;
	}
	else
	{
		ft_realloc_doble(proceso, cmd, cmd_quant);
	}
}