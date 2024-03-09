/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:04:19 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/09 12:04:20 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (current->heredoc == 0 || ((current->heredoc == 1) && last_heredoc(current) == 1))
		{
			current_fd = open(current->filename, O_RDONLY);
			if (current_fd == -1)
			{
				perror("Error");
				return (-2);
			}
			else
			{
				if (last_fd != -1)
					close(last_fd);
				last_fd = current_fd;
			}
		}
		current = current->next;
	}
	return (last_fd);
}

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
int	last_heredoc(t_fileobject *file)
{
	t_fileobject	*aux;

	aux = file;
	aux = aux->next;
	while (aux != NULL)
	{
		if (aux->heredoc == 1)
			return (0);
		aux = aux->next;
	}
	return (1);
}

char	*do_heredocs(t_process *proceso)
{
	char			*file;
	t_fileobject	*aux;
	char			*here;
	int				aux_fd;

	aux = proceso->infile;
	file = NULL;
	while (aux != NULL)
	{
		if (aux->heredoc == 1)
		{
			aux_fd = open(aux->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (file)
				free(file);
			file = ft_strdup(aux->filename);
			here = get_next_line(0);
			while (1)
			{
				if (ft_strncmp(ft_strjoin(aux->filename, "\n"), here, \
				ft_strlen(aux->filename) + 1) == 0)
					break ;
				write(aux_fd, here, ft_strlen(here));
				free(here);
				here = get_next_line(0);
			}
			free(here);
			if (last_heredoc(aux) == 0)
				unlink(aux->filename);
			close(aux_fd);
		}
		aux = aux->next;
	}
	return (file);
}
