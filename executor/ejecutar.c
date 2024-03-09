#include "../minishell.h"

void	ejecutar(char *envp[], char *path, char **comando)
{
	execve(path, comando, envp);
	write(2, "Error, comando no encontrado\n", 29);
	exit(127);
}