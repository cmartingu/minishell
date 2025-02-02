/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:19:42 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:19:43 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig_handler = 0;

int	process_execution(t_process *procesos, char ***copy_env)
{
	t_pipex	*ejecutor;
	int		status;

	if (count_process(procesos) == 1)
	{
		procesos->last_heredoc = do_heredocs(procesos);
		if (g_sig_handler != -1)
		{
			ejecutor = ini_pipex(count_process(procesos), copy_env, procesos);
			if (decide_fork(procesos) == 1)
				status = (one_process_exe(ejecutor, procesos));
			else
				status = one_process_b(ejecutor, procesos);
		}
		else
			status = 1;
		aux_close_hd(procesos);
	}
	else
		status = exe_procesos(procesos, count_process(procesos), copy_env);
	return (status);
}

void	has_cmd(char *comando, char ***copy_env, int *status)
{
	t_process		*procesos;

	add_history(comando);
	if (strncmp(comando, "history -c", strlen(comando)) == 0)
		rl_clear_history();
	else
	{
		procesos = tokenization_string(comando, *copy_env, *status);
		if (procesos == NULL)
		{
			if (all_spaces(comando) == -1)
			{
				printf("Error: syntax error\n");
				*status = 258;
			}
		}
		else
			*status = process_execution(procesos, copy_env);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char			*comando;
	char			**copy_env;
	int				status;

	argc = 0;
	status = 0;
	argv = NULL;
	copy_env = copy_array(env);
	while (1)
	{
		if (ini_signals() == -1)
			return (EXIT_FAILURE);
		comando = readline("minishell>");
		if (!comando)
			exit(EXIT_SUCCESS);
		if (*comando)
			has_cmd(comando, &copy_env, &status);
	}
	return (0);
}
