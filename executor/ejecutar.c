/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ejecutar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:17:01 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 11:17:02 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ejecutar(char *envp[], char *path, char **comando)
{
	execve(path, comando, envp);
	write(2, "Error, comando no encontrado\n", 29);
	exit(127);
}

void	do_various_builtins(t_process *procesos, t_macro_pipex *ejecutor)
{
	if (strncmp(procesos->command[0], "export", \
	ft_strlen(procesos->command[0])) == 0)
		do_export(procesos->command, ejecutor->c_env);
	else if (strncmp(procesos->command[0], "echo", \
	ft_strlen(procesos->command[0])) == 0)
		do_echo(procesos->command);
	else if (strncmp(procesos->command[0], "pwd", \
	ft_strlen(procesos->command[0])) == 0)
		do_pwd();
	else if (strncmp(procesos->command[0], "cd", \
	ft_strlen(procesos->command[0])) == 0)
		do_cd(procesos->command, *(ejecutor->c_env));
	else if (strncmp(procesos->command[0], "unset", \
	ft_strlen(procesos->command[0])) == 0)
		do_unset(procesos->command, ejecutor->c_env);
	else if (strncmp(procesos->command[0], "env", \
	ft_strlen(procesos->command[0])) == 0)
		do_env(*(ejecutor->c_env));
	else if (strncmp(procesos->command[0], "exit", \
	ft_strlen(procesos->command[0])) == 0)
		do_exit(procesos->command);
}
