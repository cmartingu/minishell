/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:38:20 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/10 14:38:20 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_process(t_process *aux_procesos, t_macro_pipex *common, \
int j, int process_num)
{
	aux_procesos->last_inf = check_infiles(aux_procesos);
	if (aux_procesos->last_inf == -2)
		exit(1);
	aux_procesos->last_out = check_outfiles(aux_procesos);
	if (aux_procesos->last_inf == -1 && process_num != common->num_process - 1)
		dup2((common->pipes)[j - 1][0], STDIN_FILENO);
	else if (aux_procesos->last_inf != -1)
	{
		dup2(aux_procesos->last_inf, STDIN_FILENO);
		close(aux_procesos->last_inf);
	}
	if (aux_procesos->last_out == -1 && process_num != 0)
		dup2((common->pipes)[j][1], STDOUT_FILENO);
	else if (aux_procesos->last_out != -1)
	{
		dup2(aux_procesos->last_out, STDOUT_FILENO);
		close(aux_procesos->last_out);
	}
}

int	wait_close_heredoc(t_macro_pipex *common, t_process *procesos)
{
	t_process	*aux_procesos;
	int			i;
	int			status;

	close_pipes(common, common->num_process);
	i = 0;
	while (i <= common->num_process)
	{
		waitpid((common->childs)[i], &status, 0);
		i++;
	}
	aux_procesos = procesos;
	while (aux_procesos != NULL)
	{
		if (aux_procesos->last_heredoc != NULL)
		{
			unlink(aux_procesos->last_heredoc);
			free(aux_procesos->last_heredoc);
		}
		aux_procesos = aux_procesos->next;
	}
	return (status);
}

void	do_childs(t_process *aux_procesos, t_macro_pipex *common, \
int j, int aux_num)
{
	char	*path;

	dup_process(aux_procesos, common, j, aux_num);
	close_pipes(common, common->num_process);
	if (decide_fork(aux_procesos) == 0)
	{
		do_various_builtins(aux_procesos, common);
		exit(0);
	}
	path = find_path(*(common->c_env), aux_procesos->command);
	ejecutar(*(common->c_env), path, aux_procesos->command);
	exit(127);
}

int	middle_childs(t_macro_pipex *common, t_process *procesos)
{
	t_process	*aux_procesos;
	int			aux_num;
	int			i;
	int			j;

	i = 0;
	j = 0;
	aux_procesos = procesos;
	aux_num = common->num_process;
	while (aux_num--)
	{
		aux_procesos->last_heredoc = do_heredocs(aux_procesos);
		(common->childs)[i] = fork();
		if ((common->childs)[i] == 0)
			do_childs(aux_procesos, common, j, aux_num);
		aux_procesos = aux_procesos->next;
		i++;
		j++;
	}
	return (wait_close_heredoc(common, procesos));
}

int	exe_procesos(t_process *procesos, int process_num, char ***copy_env)
{
	t_macro_pipex	*common;
	int				status;

	common = ini_macro_pipex(process_num, copy_env);
	status = middle_childs(common, procesos);
	return (WEXITSTATUS(status));
}
