#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>      // Para printf
# include <stdlib.h>     // Para malloc, free
# include <unistd.h>     // Para read, write, close, fork, execve, chdir, getcwd, dup, dup2, pipe, access, unlink, isatty, ttyname, ttyslot
# include <fcntl.h>      // Para open
# include <sys/wait.h>   // Para wait, waitpid, wait3, wait4
# include <sys/types.h> // 
# include <sys/resource.h>
# include <sys/stat.h>   // Para stat, fstat, lstat
# include <signal.h>     // Para signal, kill, sigaction
# include <dirent.h>     // Para opendir, readdir, closedir
# include <string.h>     // Para strerror
# include <termios.h>    // Para tcsetattr, tcgetattr
# include <curses.h>     // o <termcap.h> para funciones tgetent, tgetflag, etc., dependiendo de la biblioteca de terminal utilizada
# include <readline/readline.h> // Para readline
# include <readline/history.h>  // Para add_history
//ESTO COMPILA BIEN: cc pruebas.c -o tu_programa -I/Users/mllamas-/.brew/include -L/Users/mllamas-/.brew/lib -lreadline
//ESTE PARA CARLOS: cc minishell.c tokenization.c funciones_lib.c ctrl_handlers.c -o minishell -L/Users/carlos-m/.brew/opt/readline/lib -I/Users/carlos-m/.brew/opt/readline/include -lreadline
// Readline y History    extern void rl_replace_line (const char *, int);

typedef struct			s_fileobject
{
	char				*filename;
	struct s_fileobject	*next;
}						t_fileobject;

typedef struct			s_process
{
	char				**command;
	t_fileobject		*infile;
	t_fileobject		*outfile;
	struct s_process	*next;
}						t_process;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**save_tokens(int tam, char **cmd);
char	*next_token(char **cmd);
char	*save_word_case(char **cmd);
int		token_quant(char *cmd);
void	quant_aux(char **cmd, int *quant, int *i);
void	ctrl_C_handler(int sig);
void	ctrl_bar_handler(int sig);

#endif