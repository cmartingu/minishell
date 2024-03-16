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

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		g_sig_handler = -1;
	}
	exit(1);
}

void	read_hd(char **here, char *name, int aux_fd)
{
	while (1)
	{
		if (ft_strncmp(ft_strjoin(name, "\n"), *here, ft_strlen(name) + 1) == 0)
			break ;
		write(aux_fd, *here, ft_strlen(*here));
		free(*here);
		*here = get_next_line(0);
	}
}

void	handle_heredoc(char *name)
{
	int		aux_fd;
	char	*here;
	int		chld;
	int		stat;

	chld = fork();
	if (chld == 0)
	{
		signal(SIGINT, signal_ctlc_heredoc);
		aux_fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
		here = get_next_line(0);
		read_hd(&here, name, aux_fd);
		if (here)
			free(here);
		close(aux_fd);
		exit(0);
	}
	waitpid(chld, &stat, 0);
	if (WEXITSTATUS(stat) == 1)
		g_sig_handler = -1;
}

char	*do_heredocs(t_process *process)
{
	char			*file;
	t_fileobject	*aux;

	g_sig_handler = 2;
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
			if (g_sig_handler == -1)
				return (file);
			if (last_heredoc(aux) == 0)
				unlink(aux->filename);
		}
		aux = aux->next;
	}
	return (file);
}
