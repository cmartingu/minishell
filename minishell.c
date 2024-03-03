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

void print_fileobject_list(t_fileobject *fileobject) {
    while (fileobject != NULL) {
        printf("\tFilename: %s\n", fileobject->filename);
        fileobject = fileobject->next;
    }
}

void print_process_list(t_process *process) {
    int commandIndex;
    
    while (process != NULL) {
        printf("Command:\n");
        commandIndex = 0;
        while (process->command[commandIndex] != NULL) {
            printf("\t%s\n", process->command[commandIndex]);
            commandIndex++;
        }
        
        printf("Input Files:\n");
        if (process->infile != NULL) {
            print_fileobject_list(process->infile);
        } else {
            printf("\tNone\n");
        }
        
        printf("Output Files:\n");
        if (process->outfile != NULL) {
            print_fileobject_list(process->outfile);
        } else {
            printf("\tNone\n");
        }
        
        process = process->next;
        if (process != NULL) {
            printf("---- Next Process ----\n");
        }
    }
}

char 	**copyArray(char **old)
{
	int	len;
	int	i;
	char	**new;

	len = 0;
	while (old[len])
		len++;
	new = malloc((len + 1) * sizeof(char *));
	if (new == NULL) 
		return NULL;
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	tokenization_string(char *cmd, char **copyEnv)
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
	print_process_list(process);
	aux_process = process;
	while (aux_process != NULL)
	{
		delete_all_quot(aux_process, copyEnv);
		aux_process = aux_process->next;
	}
}



int	main(int argc, char *argv[], char *env[])
{
	char	*comando;
	argc = 0;
	argv = NULL;
	char	**copyEnv;

	copyEnv = copyArray(env);
	//struct termios termios_p;
	//struct termios termios_orig;

	//tcgetattr(STDIN_FILENO, &termios_p);
	// Guardar la configuración original para poder restaurarla más tarde
	//termios_orig = termios_p;
	
	// Modificar la configuración para que CTRL+C ^C no se muestre en el terminal
	//termios_p.c_lflag &= ~(ECHOCTL);
	
	// Aplicar la nueva configuración
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);

	/*if (signal(SIGINT, ctrl_c_handler) == SIG_ERR) {
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
				tokenization_string(comando, copyEnv);
		}
	}
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
