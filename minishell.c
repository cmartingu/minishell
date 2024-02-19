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
	if(!(proceso->infile))
		proceso->infile = new_file;
	else//Ya hay un infile, hay que añadirlo al final
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
	if(!(proceso->outfile))
		proceso->outfile = new_file;
	else//Ya hay un outfile, hay que añadirlo al final
	{
		aux_file = proceso->outfile;
		while (aux_file->next != NULL)
			aux_file = aux_file->next;
		aux_file->next = new_file;
	}
}

t_process	*procesos(int nb, char **tokens)
{
	int	i;
	t_process	*proceso;

	i = -1;
	while(nb--)
	{
		i++;
		proceso = malloc(sizeof(t_process));
		while(tokens[i] != NULL && *(tokens[i]) != '|')
		{
			if (ft_strncmp(tokens[i], "<", ft_strlen(tokens[i])) == 0)//Lo siguiente es infile
			{
				i++;
				if (*(tokens[i]) != '<' && *(tokens[i]) != '>' && *(tokens[i]) != '|')
					add_infile(proceso, tokens[i]);
			}
			if (ft_strncmp(tokens[i], ">", ft_strlen(tokens[i])) == 0)//Lo siguiente es outfile
			{
				i++;
				if (*(tokens[i]) != '<' && *(tokens[i]) != '>' && *(tokens[i]) != '|')
					add_outfile(proceso, tokens[i]);
			}
			else//Lo que hay aqui es comando
			{
			}
			i++;
		}
	}
	printf("Infiles\n\n");
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
	}
	return (NULL);
}

void	tokenization_string(char *cmd)
{
	char    **tokens;
	int		tam;
	int		forks;
	int		child;

	tam = token_quant(cmd);
	tokens = save_tokens(tam, &cmd);
	forks = pipes_quant(tokens) + 1; //Aqui ya tengo la cantidad de forks que hay que hacer, es decir la cantidad de estructuras que hay que crear
	procesos(forks, tokens);
	while (forks > 0)
	{
		child = fork();
		if (child == 0)
		{
			exit(0);
		}
		forks--;
		wait(NULL);
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

	/*if (signal(SIGINT, ctrl_C_handler) == SIG_ERR) {
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
			tokenization_string(comando);
		}
	}
	//tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}