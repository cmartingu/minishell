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

int	contador_comillas(char  *comando)
{
	int	i;
	int	cont;

	if (!comando)
		return(-1);
	i = 0;
	cont = 0;
	while (comando[i] != '\0')
	{
		if (comando[i] == '"')
			cont++;
		i++;
	}
	if (cont == 0 || cont % 2 == 0)
		return(0);
	return(-1);
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
	char    	**tokens;
	t_process	*proceso;
	int			tam;
	int			forks;

	if (contador_comillas(cmd) == -1)
	{
		printf("Minishell error: Acuerdate de cerrar las comillas\n");
		exit(1);
	}
	tam = token_quant(cmd);
	tokens = save_tokens(tam, &cmd);
	forks = pipes_quant(tokens) + 1;
	proceso = procesos(forks, tokens);
	/*while (proceso != NULL)
	{
		i = 0;
		printf("\n\n");
		printf("Infiles:\n");
		while (proceso->infile)
		{
			printf("%s\n", proceso->infile->filename);
			proceso->infile = proceso->infile->next;
		}
		printf("Outfiles:\n");
		while (proceso->outfile)
		{
			printf("%s\n", proceso->outfile->filename);
			proceso->outfile = proceso->outfile->next;
		}
		printf("Comando:\n");
		while ((proceso->command)[i] != '\0')
		{
			printf("%s\n", (proceso->command)[i]);
			i++;
		}
		proceso = proceso->next;
	}*/
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
