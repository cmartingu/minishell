/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outfiles                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:19:42 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:19:43 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_outfile(t_fileobject *current)
{
	int	current_fd;

	current_fd = -1;
	if (current->heredoc == 1)
		current_fd = open(current->filename, O_WRONLY \
	| O_CREAT | O_APPEND, 0666);
	else
		current_fd = open(current->filename, O_WRONLY \
	| O_CREAT | O_TRUNC, 0666);
	if (current_fd == -1)
	{
		perror("Error al abrir/crear el archivo");
		exit(1);
	}
	return (current_fd);
}

int	check_outfiles(t_process *process)
{
	t_fileobject	*current;
	int				current_fd;
	int				fd;
	int				is_last;

	fd = -1;
	current = process->outfile;
	is_last = 0;
	current_fd = -1;
	if (!process || !process->outfile)
		return (-1);
	while (current != NULL)
	{
		if (current->next == NULL)
			is_last = 1;
		else
			is_last = 0;
		current_fd = process_outfile(current);
		if (is_last == 1)
			fd = current_fd;
		else if (current_fd != -1)
			close(current_fd);
		current = current->next;
	}
	return (fd);
}
