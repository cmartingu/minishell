/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:19:42 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:19:43 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	open_file_check(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: No such file or directory: %s\n", filename);
		return (-2);
	}
	return (fd);
}

int	check_infiles(t_process *process)
{
	t_fileobject	*current;
	int				current_fd;
	int				last_fd;

	current_fd = -1;
	last_fd = -1;
	if (!process || !process->infile)
		return (-1);
	current = process->infile;
	while (current != NULL)
	{
		if (current->heredoc == 0
			|| ((current->heredoc == 1) && last_heredoc(current) == 1))
		{
			current_fd = open_file_check(current->filename);
			if (current_fd < 0)
				return (current_fd);
			if (last_fd != -1)
				close(last_fd);
			last_fd = current_fd;
		}
		current = current->next;
	}
	return (last_fd);
}
