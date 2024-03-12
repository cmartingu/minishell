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
	char		*comando;
	t_process	*procesos;
	t_pipex		*ejecutor;
	char		**copy_env;
	char		*lst_here;
	int			process_num;
	int			status;

	argc = 0;
	status = 0;
	argv = NULL;
	copy_env = copy_array(env);
	/*struct termios termios_p;
	struct termios termios_orig;

	tcgetattr(STDIN_FILENO, &termios_p);
	 Guardar la configuración original para poder restaurarla más tarde
	termios_orig = termios_p;
	
	 Modificar la configuración para que CTRL+C ^C no se muestre en el terminal
	termios_p.c_lflag &= ~(ECHOCTL);
	
	 Aplicar la nueva configuración
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);

	if (signal(SIGINT, ctrl_c_handler) == SIG_ERR) {
		printf("Error al establecer el manejador de SIGINT\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
		return EXIT_FAILURE;
	}
	if (signal(SIGQUIT, ctrl_bar_handler) == SIG_ERR) {
		printf("Error al establecer el manejador de SIGINT\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
		return EXIT_FAILURE;
	}*/
	while (1)
	{
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
						printf("Error: syntax error\n");
				}
				else
				{
					process_num = count_process(procesos);
					if (process_num == 1)
					{
						lst_here = do_heredocs(procesos);
						ejecutor = ini_pipex(process_num, &copy_env, procesos);
						if (decide_fork(procesos) == 1)
							status = one_process_exe(ejecutor, procesos);
						else
							status = one_process_b(ejecutor, procesos);
						if (lst_here != NULL)
						{
							unlink(lst_here);
							free(lst_here);
						}
					}
					else
					{
						status = exe_procesos(procesos, process_num, &copy_env);
					}
				}
			}
		}
	}
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
