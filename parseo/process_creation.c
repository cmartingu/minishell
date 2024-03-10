/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:09:07 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/27 16:09:08 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_file_condition(t_process *proceso, char **tok, int *i, int type)
{
	if (*(tok[*i]) != '<' && *(tok[*i]) != '>' && *(tok[*i]) != '|')
	{
		if (type == 0 || type == 1)
			add_outfile(proceso, tok[*i], type);
		else if (type == 2 || type == 3)
			add_infile(proceso, tok[*i], type - 2);
	}
}

void	add_command_condition(t_process *proceso, char **tok, int *i, int *qua)
{
	(*qua)++;
	add_cmd(proceso, tok[*i], *qua);
}

void	create_process(t_process *proceso, char **tok, int *i, int *qua)
{
	if (ft_strncmp(tok[*i], ">", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		add_file_condition(proceso, tok, i, 0);
	}
	else if (ft_strncmp(tok[*i], "<", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		add_file_condition(proceso, tok, i, 2);
	}
	else if (ft_strncmp(tok[*i], ">>", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		add_file_condition(proceso, tok, i, 1);
	}
	else if (ft_strncmp(tok[*i], "<<", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		add_file_condition(proceso, tok, i, 3);
	}
	else
		add_command_condition(proceso, tok, i, qua);
	(*i)++;
}
/*
void	create_process(t_process *proceso, char **tok, int *i, int *qua)
{
	if (ft_strncmp(tok[*i], ">", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		if (*(tok[*i]) != '<' && *(tok[*i]) != '>' && *(tok[*i]) != '|')
			add_outfile(proceso, tok[*i], 0);
	}
	else if (ft_strncmp(tok[*i], "<", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		if (*(tok[*i]) != '<' && *(tok[*i]) != '>' && *(tok[*i]) != '|')
			add_infile(proceso, tok[*i], 0);
	}
	else if (ft_strncmp(tok[*i], ">>", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		if (*(tok[*i]) != '<' && *(tok[*i]) != '>' && *(tok[*i]) != '|')
			add_outfile(proceso, tok[*i], 1);
	}
	else if (ft_strncmp(tok[*i], "<<", ft_strlen(tok[*i])) == 0)
	{
		(*i)++;
		if (*(tok[*i]) != '<' && *(tok[*i]) != '>' && *(tok[*i]) != '|')
			add_infile(proceso, tok[*i], 1);
	}
	else
	{
		(*qua)++;
		add_cmd(proceso, tok[*i], *qua);
	}
	(*i)++;
}
*/

t_process	*procesos(int nb, char **tokens)
{
	t_process	*proceso;
	t_process	*proceso_aux;
	int			i;
	int			cmd_quant;

	i = -1;
	proceso_aux = malloc(sizeof(t_process));
	proceso_aux->next = NULL;
	while (nb--)
	{
		i++;
		cmd_quant = 0;
		proceso = malloc(sizeof(t_process));
		proceso->next = NULL;
		proceso->command = NULL;
		proceso->infile = NULL;
		proceso->outfile = NULL;
		add_process_back(proceso_aux, proceso);
		while (tokens[i] != NULL && *(tokens[i]) != '|')
			create_process(proceso, tokens, &i, &cmd_quant);
	}
	proceso = proceso_aux->next;
	free(proceso_aux);
	return (proceso);
}

void	save_final_quot(char **aux, char *cmd, int *i, int *j)
{
	(*aux)[*j] = cmd[*i];
	(*i)++;
	(*j)++;
}
