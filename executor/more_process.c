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

int	decide_fork(t_process *process)
{
	if (strncmp(process->command[0], "export", \
	ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "echo", \
	ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "pwd", \
	ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "cd", \
	ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "unset", \
	ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "env", \
	ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "exit", \
	ft_strlen(process->command[0])) == 0)
		return (0);
	else
		return (1);
}

int	middle_childs(t_macro_pipex *common, t_process *procesos, int process_num)
{
	t_process	*aux_procesos;
	char		*path;
	int			aux_num;
	int			status;
	int			i;
	int			j;

	i = 0;
	j = 0;
	aux_procesos = procesos;
	aux_num = process_num;
	while (process_num--)
	{
		aux_procesos->last_heredoc = do_heredocs(aux_procesos);
		(common->childs)[i] = fork();
		if ((common->childs)[i] == 0)
		{
			aux_procesos->last_inf = check_infiles(aux_procesos);
			if (aux_procesos->last_inf == -2)
				exit(1);
			aux_procesos->last_out = check_outfiles(aux_procesos);
			if (aux_procesos->last_inf == -1 && process_num != aux_num - 1)
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
			close_pipes(common, aux_num);
			path = find_path(*(common->c_env), aux_procesos->command);
			ejecutar(*(common->c_env), path, aux_procesos->command);
			exit(127);
		}
		aux_procesos = aux_procesos->next;
		i++;
		j++;
	}
	close_pipes(common, aux_num);
	i = 0;
	while (i <= aux_num)
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

int	exe_procesos(t_process *procesos, int process_num, char ***copy_env)
{
	t_macro_pipex	*common;
	int				status;

	common = ini_macro_pipex(process_num, copy_env);
	status = middle_childs(common, procesos, process_num);
	return (status);
}
