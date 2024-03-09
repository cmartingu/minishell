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

void	close_pipes(t_macro_pipex *pipexx, int process_num)
{
	int	i;

	i = 0;
	while (i < (process_num - 1))
	{
		close((pipexx->pipes)[i][0]);
		close((pipexx->pipes)[i][1]);
		i++;
	}
}

t_pipex	*ini_pipex(int process_num, char ***envp, t_process *proceso)
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
	pipexx->last_inf = check_infiles(proceso);
	if (pipexx->last_inf != -2)
		pipexx->last_out = check_outfiles(proceso);
	else
		pipexx->last_out = -1;
	return (pipexx);
}

t_macro_pipex	*ini_macro_pipex(int process_num, char ***envp)
{
	t_macro_pipex	*pipexx;

	pipexx = malloc(sizeof(t_macro_pipex));
	if (!pipexx)
		perror("Minishell");
	pipexx->pipes = create_pipes(process_num - 1);
	pipexx->childs = malloc(process_num * sizeof(int));
	if (!pipexx->childs)
		perror("Minishell");
	pipexx->c_env = envp;
	return (pipexx);
}



int	middle_childs(t_macro_pipex *common, t_process *procesos, int process_num)
{
	char	*path;
	int		status;
	int		i;
	int		aux_num;
	int		j;

	i = 0;
	j = 0;
	aux_num = process_num;
	while (process_num--)
	{
		procesos->last_heredoc = do_heredocs(procesos);
		(common->childs)[i] = fork();
		if ((common->childs)[i] == 0)
		{
			procesos->last_inf = check_infiles(procesos);
			if (procesos->last_inf == -2)
				exit(1);
			procesos->last_out = check_outfiles(procesos);
			if (procesos->last_inf == -1 && process_num != aux_num - 1)
				dup2((common->pipes)[0][0], STDIN_FILENO); //cambiar el 0 por j
			else if (procesos->last_inf != -1)
			{
				dup2(procesos->last_inf, STDIN_FILENO);
				close(procesos->last_inf);
			}
			if (procesos->last_out == -1 && process_num != 0)
				dup2((common->pipes)[0][1], STDOUT_FILENO); //cambiar el 0 por (j - 1)
			else if (procesos->last_out != -1)
			{
				dup2(procesos->last_out, STDOUT_FILENO);
				close(procesos->last_out);
			}
			close_pipes(common, aux_num);
			path = find_path(*(common->c_env), procesos->command);
			ejecutar(*(common->c_env), path, procesos->command);
			exit(127);
		}
		procesos = procesos->next;
		i++;
		j++;
	}
	close_pipes(common, aux_num);
	//cerrar todos heredocs
	i = 0;
	while (i <= aux_num)
	{
		waitpid((common->childs)[i], &status, 0);
		i++;
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
				procesos = tokenization_string(comando, copy_env);
				process_num = count_process(procesos);
				if (process_num ==  1)
				{
					lst_here = do_heredocs(procesos);
					ejecutor = ini_pipex(process_num, &copy_env, procesos);
					if (decide_fork(procesos) == 1)
						status = one_process_exe(ejecutor, procesos);
					else
						one_process_b(ejecutor, procesos);
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
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
