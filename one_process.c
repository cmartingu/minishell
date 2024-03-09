/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:03:09 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/09 12:03:10 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_process_b(t_pipex *ejecutor, t_process *procesos)
{
	int	original_stdin;
	int	original_stdout;

	if (ejecutor->last_inf == -2)
		return ;
	if (ejecutor->last_inf != -1)
	{
		original_stdin = dup(STDIN_FILENO);
		dup2(ejecutor->last_inf, STDIN_FILENO);
	}
	if (ejecutor->last_out != -1)
	{
		original_stdout = dup(STDOUT_FILENO);
		dup2(ejecutor->last_out, STDOUT_FILENO);
	}
	if (strncmp(procesos->command[0], "export", ft_strlen(procesos->command[0])) == 0)
		do_export(procesos->command, ejecutor->c_env);
	else if (strncmp(procesos->command[0], "echo", ft_strlen(procesos->command[0])) == 0)
		do_echo(procesos->command);
	else if (strncmp(procesos->command[0], "pwd", ft_strlen(procesos->command[0])) == 0)
		do_pwd();
	else if (strncmp(procesos->command[0], "cd", ft_strlen(procesos->command[0])) == 0)
		do_cd(procesos->command, *(ejecutor->c_env));
	else if (strncmp(procesos->command[0], "unset", ft_strlen(procesos->command[0])) == 0)
		do_unset(procesos->command, *(ejecutor->c_env));
	else if (strncmp(procesos->command[0], "env", ft_strlen(procesos->command[0])) == 0)
		do_env(*(ejecutor->c_env));
	else if (strncmp(procesos->command[0], "exit", ft_strlen(procesos->command[0])) == 0)
		do_exit(procesos->command);
	if (ejecutor->last_inf != -1)
		dup2(original_stdin, STDIN_FILENO);
	if (ejecutor->last_out != -1)
		dup2(original_stdout, STDOUT_FILENO);
}

int	one_process_exe(t_pipex *ejecutor, t_process *procesos)
{
	char	*path;
	int		status;

	ejecutor->childs[0] = fork();
	if (ejecutor->childs[0] == 0)
	{
		if (ejecutor->last_inf == -2)
			exit(1);
		if (ejecutor->last_inf != -1)
			dup2(ejecutor->last_inf, STDIN_FILENO);
		if (ejecutor->last_out != -1)
			dup2(ejecutor->last_out, STDOUT_FILENO);
		path = find_path(*(ejecutor->c_env), procesos->command);
		ejecutar(*(ejecutor->c_env), path, procesos->command);
	}
	waitpid(ejecutor->childs[0], &status, 0);
	return (status);
}
