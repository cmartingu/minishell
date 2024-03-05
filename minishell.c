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
		printf("\tFilename: %s\n", fileobject->filename);
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
		if (process->infile != NULL)
		{
			print_fileobject_list(process->infile);
		}
		else
		{
			printf("\tNone\n");
		}
		printf("Output Files:\n");
		if (process->outfile != NULL)
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
	//print_process_list(process);
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

int	main(int argc, char *argv[], char *env[])
{
	char		*comando;
	t_process	*procesos;
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
				print_process_list(procesos);
				process_num = count_process(procesos);
			}
		}
	}
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
