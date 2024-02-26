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

int	end_quotation(char **cmd, char quot)
{
	(*cmd)++;
	while ((**cmd) != '\0' && (**cmd) != quot)
		(*cmd)++;
	if ((**cmd) == quot)
		return (0);
	return (-1);
}

int	contador_comillas(char  *comando)
{
	char	*aux_cmd;

	if (!comando)
		return(-1);
	aux_cmd = comando;
	while (*comando != '\0')
	{
		if (*comando == '"')
		{
			if (end_quotation(&comando, '"') == -1)
				return (-1);
		}
		else if (*comando == '\'')
		{
			if (end_quotation(&comando, '\'') == -1)
				return (-1);
		}
		comando++;
	}
	comando = aux_cmd;
	return(0);
}

void	process_creation(t_process *proceso, char **tokens, int *i, int *cmd_quant)
{
	if (ft_strncmp(tokens[*i], "<", ft_strlen(tokens[*i])) == 0)
	{
		(*i)++;
		if (*(tokens[*i]) != '<' && *(tokens[*i]) != '>' && *(tokens[*i]) != '|')
			add_infile(proceso, tokens[*i]);
	}
	else if (ft_strncmp(tokens[*i], ">", ft_strlen(tokens[*i])) == 0)
	{
		(*i)++;
		if (*(tokens[*i]) != '<' && *(tokens[*i]) != '>' && *(tokens[*i]) != '|')
			add_outfile(proceso, tokens[*i]);
	}
	else
	{
		(*cmd_quant)++;
		add_cmd(proceso, tokens[*i], *cmd_quant);
	}
	(*i)++;
}

t_process	*procesos(int nb, char **tokens)
{
	t_process	*proceso;
	t_process	*proceso_aux;
	int			i;
	int			cmd_quant;

	i = -1;
	proceso_aux = malloc(sizeof(t_process));
	proceso_aux->next = NULL;
	while (nb--)
	{
		i++;
		cmd_quant = 0;
		proceso = malloc(sizeof(t_process));
		proceso->next = NULL;
		add_process_back(proceso_aux, proceso);
		while (tokens[i] != NULL && *(tokens[i]) != '|')
			process_creation(proceso, tokens, &i, &cmd_quant);
	}
	proceso = proceso_aux->next;
	free(proceso_aux);
	return (proceso);
}

void	tokenization_string(char *cmd)
{
	t_process	*process;
	t_process	*aux_process;
	t_fileobject	*aux_file;
	char		**aux_cmd
	char    	**tokens;
	int		tam;
	int		forks;

	if (contador_comillas(cmd) == -1)
	{
		printf("Minishell error: Acuerdate de cerrar las comillas\n");
		exit(1);
	}
	tam = token_quant(cmd);
	tokens = save_tokens(tam, &cmd);
	forks = pipes_quant(tokens) + 1;
	process = procesos(forks, tokens);
	delete_quotation(process->command);
	aux_process = process;
	while (aux_process != NULL)
	{
		aux_file = aux_process->infile;
		while (aux_file != NULL)
		{
			(aux_file->filename) = delete_quotation(&(aux_file->filename));
			aux_file = aux_file->next;
		}
		aux_file = aux_process->outfile;
		while (aux_file != NULL)
		{
			(aux_file->filename) = delete_quotation(&(aux_file->filename));
			aux_file = aux_file->next;
		}
		aux_command = aux_process->command;
		if (aux_command)
			while ((*aux_command) != NULL)
			{
				(*aux_command) = delete_quotation(aux_command);
				aux_command++;
			}
		aux_process = aux_process->next;
	}
}

int main(void)
{
	char	*comando;
	//struct termios termios_p;
	//struct termios termios_orig;

	//tcgetattr(STDIN_FILENO, &termios_p);
	// Guardar la configuración original para poder restaurarla más tarde
	//termios_orig = termios_p;
	
	// Modificar la configuración para que CTRL+C no se muestre en el terminal
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
				tokenization_string(comando);
		}
	}
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
