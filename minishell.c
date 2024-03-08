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

/*void	print_fileobject_list(t_fileobject *fileobject)
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
}*/

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

void	do_heredocs(t_process *proceso)
{
	t_fileobject	*aux;
	char			*here;
	int				aux_fd;

	aux = proceso->infile;
	while (aux != NULL)
	{
		if (aux->heredoc == 1)
		{
			aux_fd = open(aux->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
			here = get_next_line(0);
			while (1)
			{
				if (ft_strncmp(ft_strjoin(aux->filename, "\n"), here, \
				ft_strlen(aux->filename) + 1) == 0)
					break ;
				write(aux_fd, here, ft_strlen(here));
				free(here);
				here = get_next_line(0);
			}
			free(here);
			if (last_heredoc(aux) == 0)
				unlink(aux->filename);
			close(aux_fd);
		}
		aux = aux->next;
	}
}


int	check_infiles(t_process *process)
{
	t_fileobject	*current;
	int				current_fd;
	int				last_fd;

	current_fd = -1;
	last_fd = -1;
	if (!process || !process->infile)
		return (-1);
	current = process->infile;
	while (current != NULL)
	{
		if (current->heredoc == 0 || ((current->heredoc == 1) && last_heredoc(current) == 1))
		{
			current_fd = open(current->filename, O_RDONLY);
			if (current_fd == -1)
			{
				perror("Error al abrir el infile");
				exit(1);
			}
			else
			{
				if (last_fd != -1)
					close(last_fd);
				last_fd = current_fd;
			}
		}
		current = current->next;
	}
	return (last_fd);
}

int	process_outfile(t_fileobject *current)
{
	int	current_fd;

	current_fd = -1;
	if (current->heredoc == 1)
		current_fd = open(current->filename, O_WRONLY \
	| O_CREAT | O_APPEND, 0666);
	else
		current_fd = open(current->filename, O_WRONLY \
	| O_CREAT | O_TRUNC, 0666);
	if (current_fd == -1)
	{
		perror("Error al abrir/crear el archivo");
		exit(1);
	}
	return (current_fd);
}

int	check_outfiles(t_process *process)
{
	t_fileobject	*current;
	int				current_fd;
	int				fd;
	int				is_last;

	fd = -1;
	current = process->outfile;
	is_last = 0;
	current_fd = -1;
	if (!process || !process->outfile)
		return (-1);
	while (current != NULL)
	{
		if (current->next == NULL)
			is_last = 1;
		else
			is_last = 0;
		current_fd = process_outfile(current);
		if (is_last == 1)
			fd = current_fd;
		else if (current_fd != -1)
			close(current_fd);
		current = current->next;
	}
	return (fd);
}

t_pipex	*ini_pipex(int process_num, char **envp, t_process *proceso)
{
	t_pipex	*pipexx;

	pipexx = malloc(sizeof(t_pipex));
	if (!pipexx)
		perror("Minishell");
	pipexx->pipes = create_pipes(process_num - 1);
	pipexx->childs = malloc(process_num * sizeof(int));
	if (!pipexx->childs)
		perror("Minishell");
	pipexx->c_env = envp;
	pipexx->last_out = check_outfiles(proceso);
	pipexx->last_inf = check_infiles(proceso);
	return (pipexx);
}

int	main(int argc, char *argv[], char *env[])
{
	char		*comando;
	t_process	*procesos;
	t_pipex		*ejecutor;
	char		**copy_env;
	int			process_num;
	char		*path;
	int			status;
	int			original_stdin;
	int			original_stdout;
	//int			salida_std;

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
			/*else if (strncmp(comando, "exit", 4) == 0)
			{
				printf("exit\n");
				//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
				exit(0);
			}*/
			else
			{
				procesos = tokenization_string(comando, copy_env);
				process_num = count_process(procesos);
				if (process_num ==  1)
				{

					do_heredocs(procesos);
					ejecutor = ini_pipex(process_num, copy_env, procesos);
					if (decide_fork(procesos) == 1)
					{
						ejecutor->childs[0] = fork();
						if (ejecutor->childs[0] == 0)
						{
							if (ejecutor->last_inf != -1)
								dup2(ejecutor->last_inf, STDIN_FILENO);
							if (ejecutor->last_out != -1)
								dup2(ejecutor->last_out, STDOUT_FILENO);
							path = find_path(ejecutor->c_env, procesos->command);
							ejecutar(ejecutor->c_env, path, procesos->command);
						}
						waitpid(ejecutor->childs[0], &status, 0);
					}
					else
					{
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
							do_cd(procesos->command, ejecutor->c_env);
						//else if (strncmp(process->command[0], "unset", ft_strlen(process->command[0])) == 0)
						//	do_unset();
						else if (strncmp(procesos->command[0], "env", ft_strlen(procesos->command[0])) == 0)
							do_env(ejecutor->c_env);
						else if (strncmp(procesos->command[0], "exit", ft_strlen(procesos->command[0])) == 0)
							do_exit(procesos->command);
						dup2(original_stdin, STDIN_FILENO);
						dup2(original_stdout, STDOUT_FILENO);
					}
				}
				/*else
				{
					ejecutor = ini_pipex(process_num, copy_env);//Fork para cada proceso. 
				}*/
			}
		}
	}
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
