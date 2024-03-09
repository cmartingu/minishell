/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printea_procesos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:06:05 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/09 12:06:06 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_fileobject_list(t_fileobject *fileobject)
{
	while (fileobject != NULL)
	{
		printf("\tFilename: %s		Flag: %d\n", fileobject->filename, fileobject->heredoc);
		fileobject = fileobject->next;
	}
}

void	print_process_list(t_process *process)
{
	int	command_index;

	while (process != NULL)
	{
		printf("Command:\n");
		if (process->command != NULL)
		{
			command_index = 0;
			while (process->command[command_index] != NULL)
			{
				printf("\t%s\n", process->command[command_index]);
				command_index++;
			}
		}
		printf("Input Files:\n");
		if (process->infile)
		{
			print_fileobject_list(process->infile);
		}
		else
		{
			printf("\tNone\n");
		}
		printf("Output Files:\n");
		if (process->outfile)
		{
			print_fileobject_list(process->outfile);
		}
		else
		{
			printf("\tNone\n");
		}
		process = process->next;
		if (process != NULL)
		{
			printf("---- Next Process ----\n");
		}
	}
}
