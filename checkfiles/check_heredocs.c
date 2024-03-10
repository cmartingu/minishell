/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:19:42 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:19:43 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	handle_heredoc(char *name)
{
	int		aux_fd;
	char	*here;

	aux_fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	here = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(ft_strjoin(name, "\n"), here, ft_strlen(name) + 1) == 0)
			break ;
		write(aux_fd, here, ft_strlen(here));
		free(here);
		here = get_next_line(0);
	}
	free(here);
	close(aux_fd);
}

char	*do_heredocs(t_process *process)
{
	char			*file;
	t_fileobject	*aux;

	aux = process->infile;
	file = NULL;
	while (aux != NULL)
	{
		if (aux->heredoc == 1)
		{
			if (file)
				free(file);
			file = ft_strdup(aux->filename);
			handle_heredoc(aux->filename);
			if (last_heredoc(aux) == 0)
				unlink(aux->filename);
		}
		aux = aux->next;
	}
	return (file);
}
