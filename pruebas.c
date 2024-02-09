#include <string.h>
#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para malloc, free
#include <unistd.h>     // Para read, write, close, fork, execve, chdir, getcwd, dup, dup2, pipe, access, unlink, isatty, ttyname, ttyslot
#include <fcntl.h>      // Para open
#include <sys/wait.h>   // Para wait, waitpid, wait3, wait4
#include <sys/types.h> // 
#include <sys/resource.h>
#include <sys/stat.h>   // Para stat, fstat, lstat
#include <signal.h>     // Para signal, kill, sigaction
#include <dirent.h>     // Para opendir, readdir, closedir
#include <string.h>     // Para strerror
#include <termios.h>    // Para tcsetattr, tcgetattr
#include <curses.h>     // o <termcap.h> para funciones tgetent, tgetflag, etc., dependiendo de la biblioteca de terminal utilizada
#include <readline/readline.h> // Para readline
#include <readline/history.h>  // Para add_history
//ESTO COMPILA BIEN: gcc pruebas.c -o tu_programa -I/Users/mllamas-/.brew/include -L/Users/mllamas-/.brew/lib -lreadline
//ESTE PARA CARLOS: cc minishell.c -o minishell -L/Users/carlos-m/.brew/opt/readline/lib -I/Users/carlos-m/.brew/opt/readline/include -lreadline
// Readline y History    extern void rl_replace_line (const char *, int);


void ctrl_C_handler(int sig) {
	printf("\n");
	rl_on_new_line(); // Prepara readline para recibir una nueva línea
	rl_replace_line("", 0); // Limpia el buffer de la línea actual en readline
	rl_redisplay(); // Vuelve a mostrar el prompt
}

void ctrl_bar_handler(int sig) {
	return;
}

int token_quant(char *cmd)
{
	int		i;
	int		quant;

	quant = 0;
	i = 0;
	while(cmd[i] != '\0')
	{
		while(cmd[i] == ' ')
			i++;
		if (cmd[i] != '\0' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
			quant++;
		while(cmd[i] != ' ' && cmd[i] != '\0')
		{
			if ((cmd[i] == '<' && cmd[i + 1] == '<') || (cmd[i] == '>' && cmd[i + 1] == '>'))
			{
				quant++;
				i++;
				i++;
				if (cmd[i] != ' ' && cmd[i] != '\0' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
					quant++;
			}
			else if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
			{
				quant++;
				i++;
				if (cmd[i] != ' ' && cmd[i] != '\0' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
				{
					quant++;
					i++;
				}
			}
			else
				i++;
		}
	}
	return (quant);
}

char	*next_token(char **cmd)
{
	int		i;
	int		skip_tam;
	char	*aux_tkn;

	i = 0;
	if ((*cmd)[i] == '|')
	{
		(*cmd)++;
		return (strdup("|"));
	}
	else if ((*cmd)[i] == '>')
	{
		(*cmd)++;
		if ((*cmd)[i] == '>')
		{
			(*cmd)++;
			return (strdup(">>"));
		}
		return (strdup(">"));
	}
	else if ((*cmd)[i] == '<')
	{
		(*cmd)++;
		if ((*cmd)[i] == '<')
		{
			(*cmd)++;
			return (strdup("<<"));
		}
		return (strdup("<"));
	}
	else //Es una palabra si llega aqui
	{
		while ((*cmd)[i] != '<' && (*cmd)[i] != '>' && (*cmd)[i] != '|' && (*cmd)[i] != ' ' && (*cmd)[i] != '\0')// Mide el tamaño de la palabra
			i++;
		if (i == 0)
			return (NULL);
		aux_tkn = malloc(i + 1);
		aux_tkn[i] = '\0';
		skip_tam = i;
		while (i--)
			aux_tkn[i] = (*cmd)[i];
		while (skip_tam-- > 0)
			(*cmd)++;
	}
	return (aux_tkn);
}

char	**save_tokens(int tam, char **cmd)
{
	char	**tokens;
	char	*aux_cmd;
	int		j;

	j = 0;
	aux_cmd = (*cmd);
	tokens = malloc((tam + 1) * sizeof(char *));
	if (!tokens)
	{
		write(2, "Error, malloc error\n", 20);
		exit(1);
	}
	while(**cmd != '\0')
	{
		while (*(*cmd) == ' ')
			(*cmd)++;
		if (*(*cmd) != '\0')
		{
			tokens[j] = next_token(cmd);
			j++;
		}
	}
	(*cmd) = aux_cmd;
	tokens[j] = NULL;
	return (tokens);
}

void	tokenization_string(char *cmd)
{
	char    **tokens;
	int		tam;

	tam = token_quant(cmd);
	tokens = save_tokens(tam, &cmd);
}

int main(void)
{
	char	*comando;
	struct termios termios_p;
	struct termios termios_orig;

	tcgetattr(STDIN_FILENO, &termios_p);
	// Guardar la configuración original para poder restaurarla más tarde
	termios_orig = termios_p;
	
	// Modificar la configuración para que CTRL+C no se muestre en el terminal
	termios_p.c_lflag &= ~(ECHOCTL);
	
	// Aplicar la nueva configuración
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);

	if (signal(SIGINT, ctrl_C_handler) == SIG_ERR) {
		printf("Error al establecer el manejador de SIGINT\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
		return EXIT_FAILURE;
	}
	if (signal(SIGQUIT, ctrl_bar_handler) == SIG_ERR) {
		printf("Error al establecer el manejador de SIGINT\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
		return EXIT_FAILURE;
	}
	
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
				tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
				exit(0);
			}
			tokenization_string(comando);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_orig);
	return (0);
}
