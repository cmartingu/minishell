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

int	pipes_quant(char **tokens)
{
	int		pipes;
	int		i;

	i = 0;
	pipes = 0;
	while (tokens[i] != NULL)
	{
		if (*(tokens[i]) == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

void	add_infile(t_process *proceso, char *inf)
{
	t_fileobject	*new_file;
	t_fileobject	*aux_file;

	new_file = malloc(sizeof(new_file));
	if (!new_file)
	{
		printf("Error, malloc error\n");
		exit(1);
	}
	new_file->filename = ft_strdup(inf);
	new_file->next = NULL;
	if (!(proceso->infile))
		proceso->infile = new_file;
	else
	{
		aux_file = proceso->infile;
		while (aux_file->next != NULL)
			aux_file = aux_file->next;
		aux_file->next = new_file;
	}
}

void	add_outfile(t_process *proceso, char *outf)
{
	t_fileobject	*new_file;
	t_fileobject	*aux_file;

	new_file = malloc(sizeof(new_file));
	if (!new_file)
	{
		printf("Error, malloc error\n");
		exit(1);
	}
	new_file->filename = ft_strdup(outf);
	new_file->next = NULL;
	if (!(proceso->outfile))
		proceso->outfile = new_file;
	else
	{
		aux_file = proceso->outfile;
		while (aux_file->next != NULL)
			aux_file = aux_file->next;
		aux_file->next = new_file;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char **ft_realloc_doble(char **cmd, char *str, int tam)
{
	char	**final_cmd;

	final_cmd = malloc((tam + 1) * sizeof(char *));
	if (!final_cmd)
	{
		printf("Error, malloc error");
		exit(1);
	}
	final_cmd[tam] = NULL;
	final_cmd[tam - 1] = ft_strdup(str);
	tam--;
	while (tam--)
		final_cmd[tam] = ft_strdup(cmd[tam]);
	free_arr(cmd);
	return (final_cmd);
}

void	add_cmd(t_process *proceso, char *cmd)
{
	if (!(proceso->command))
	{
		proceso->command = malloc(2 * sizeof(char *));
		if (!(proceso->command))
		{
			printf("Error, malloc error");
			exit(1);
		}
		(proceso->command)[0] = ft_strdup(cmd);
		(proceso->command)[1] = NULL;
	}
	else//Ya hay comando, hay que guardarlo a continuacion
	{
	}
}

t_process	*procesos(int nb, char **tokens)
{
	t_process	*proceso;
	int			i;
	int			cmd_quant;

	i = -1;
	while (nb--)
	{
		i++;
		cmd_quant = 0;
		proceso = malloc(sizeof(t_process));
		while (tokens[i] != NULL && *(tokens[i]) != '|')
		{
			if (ft_strncmp(tokens[i], "<", ft_strlen(tokens[i])) == 0)
			{
				i++;
				if (*(tokens[i]) != '<' && *(tokens[i]) != '>' && *(tokens[i]) != '|')
					add_infile(proceso, tokens[i]);
			}
			if (ft_strncmp(tokens[i], ">", ft_strlen(tokens[i])) == 0)
			{
				i++;
				if (*(tokens[i]) != '<' && *(tokens[i]) != '>' && *(tokens[i]) != '|')
					add_outfile(proceso, tokens[i]);
			}
			else
			{
				cmd_quant++;
				add_cmd(proceso, tokens[i]);
			}
			i++;
		}
	}
	/*printf("Infiles\n\n");
	while (proceso->infile)
	{
		printf("%s\n", proceso->infile->filename);
		proceso->infile = proceso->infile->next;
	}
	printf("Outfiles:\n\n");
	while (proceso->outfile)
	{
		printf("%s\n", proceso->outfile->filename);
		proceso->outfile = proceso->outfile->next;
	}*/
	return (NULL);
}

void	tokenization_string(char *cmd)
{
	char    **tokens;
	int		tam;
	int		forks;

	tam = token_quant(cmd);
	tokens = save_tokens(tam, &cmd);
	forks = pipes_quant(tokens) + 1;
	procesos(forks, tokens);
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
