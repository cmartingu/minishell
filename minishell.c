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

void	print_fileobject_list(t_fileobject *fileobject)
{
	while (fileobject != NULL)
	{
		printf("\tFilename: %s		Flag: %d\n", fileobject->filename, fileobject->heredoc);
		fileobject = fileobject->next;
	}
}

void	print_process_list(t_process *process)
{
	int	command_index;

	while (process != NULL)
	{
		printf("Command:\n");
		if (process->command != NULL)
		{
			command_index = 0;
			while (process->command[command_index] != NULL)
			{
				printf("\t%s\n", process->command[command_index]);
				command_index++;
			}
		}
		printf("Input Files:\n");
		if (process->infile)
		{
			print_fileobject_list(process->infile);
		}
		else
		{
			printf("\tNone\n");
		}
		printf("Output Files:\n");
		if (process->outfile)
		{
			print_fileobject_list(process->outfile);
		}
		else
		{
			printf("\tNone\n");
		}
		process = process->next;
		if (process != NULL)
		{
			printf("---- Next Process ----\n");
		}
	}
}

char	**copy_array(char **old)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (old[len])
		len++;
	new = malloc((len + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

t_process	*tokenization_string(char *cmd, char **copy_env)
{
	t_process		*process;
	t_process		*aux_process;
	char			**tokens;
	int				tam;
	int				forks;

	if (contador_comillas(cmd) == -1)
	{
		printf("Minishell error: Acuerdate de cerrar las comillas\n");
		exit(1);
	}
	tam = token_quant(cmd);
	tokens = save_tokens(tam, &cmd);
	forks = pipes_quant(tokens) + 1;
	process = procesos(forks, tokens);
	aux_process = process;
	while (aux_process != NULL)
	{
		delete_all_quot(aux_process, copy_env);
		aux_process = aux_process->next;
	}
	return (process);
}

int	count_process(t_process *procesos)
{
	t_process	*aux;
	int			i;

	aux = procesos;
	i = 0;
	while (aux != NULL)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

/*t_pipex	*ini_pipex(int process_num, char **envp)
{
	t_pipex	*pipexx;

	pipexx = malloc(sizeof(t_pipex));
	pipexx->pipes = create_pipes(process_num - 1);
	pipexx->c_env = envp;
	pipexx->childs = malloc(process_num * sizeof(int));
	return (pipexx);
}*/

int	decide_fork(t_process *process)
{
	if (strncmp(process->command[0], "export", ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "echo", ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "pwd", ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "cd", ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "unset", ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "env", ft_strlen(process->command[0])) == 0)
		return (0);
	else if (strncmp(process->command[0], "exit", ft_strlen(process->command[0])) == 0)
		return (0);
	else
		return (1);
}

void	do_heredocs(t_process *proceso)
{
	t_fileobject	*aux;
	char			*here;
	char			*final;

	aux = proceso->infile;
	final = "\0";
	while (aux != NULL)
	{
		if (aux->heredoc == 1)
		{
			here = get_next_line(0);
			while (ft_strncmp(aux->filename, here, ft_strlen(aux->filename)) != 0)
			{
				final = ft_strjoin(final, here);
				here = get_next_line(0);
				printf("Final:%s  Here:%s\n", final, here);
			}
		}
		aux = aux->next;
	}
	printf("%s\n", final);
}

int	main(int argc, char *argv[], char *env[])
{
	char		*comando;
	t_process	*procesos;
	//t_pipex		*ejecutor;
	char		**copy_env;
	int			process_num;

	argc = 0;
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
			else if (strncmp(comando, "exit", 4) == 0)
			{
				printf("exit\n");
				//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
				exit(0);
			}
			else
			{
				procesos = tokenization_string(comando, copy_env);
				//print_process_list(procesos);
				process_num = count_process(procesos);
				do_heredocs(procesos);
				/*if (process_num ==  1)
				{
					//Comprobar heredocs y hacerlos
					//comprobar inf y outf
					if (decide_fork(procesos) == 0)
						//ejecutar builtins
					else
						//Fork y ejecutar con execve.
				}
				else
				{
					ejecutor = ini_pipex(process_num, copy_env);//Fork para cada proceso. 
				}*/
			}
		}
	}
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
