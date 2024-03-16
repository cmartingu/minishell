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

int	all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	char			*comando;
	t_process		*procesos;
	t_pipex			*ejecutor;
	char			**copy_env;
	char			*lst_here;
	int				status;

	argc = 0;
	status = 0;
	argv = NULL;
	g_sig_handler = 0;
	copy_env = copy_array(env);
	while (1)
	{
		if (ini_signals() == -1)
			return (EXIT_FAILURE);
		comando = readline("minishell>");
		if (!comando)
			exit(EXIT_SUCCESS);
		if (*comando)
		{
			add_history(comando);
			if (strncmp(comando, "history -c", strlen(comando)) == 0)
				rl_clear_history();
			else
			{
				procesos = tokenization_string(comando, copy_env, status);
				if (procesos == NULL)
				{
					if (all_spaces(comando) == -1)
					{
						printf("Error: syntax error\n");
						status = 258;
					}
				}
				else
				{
					if (count_process(procesos) == 1)
					{
						lst_here = do_heredocs(procesos);
						if (g_sig_handler != -1)
						{
							ejecutor = ini_pipex(count_process(procesos), &copy_env, procesos);
							if (decide_fork(procesos) == 1)
								status = one_process_exe(ejecutor, procesos);
							else
								status = one_process_b(ejecutor, procesos);
						}
						if (lst_here != NULL)
						{
							unlink(lst_here);
							free(lst_here);
						}
					}
					else
						status = exe_procesos(procesos, count_process(procesos), &copy_env);
				}
			}
		}
	}
	return (0);
}
