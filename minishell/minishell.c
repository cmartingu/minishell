#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	*comando;

	while (1)
	{
		comando = readline("minishell>");
		if (comando && *comando)
        	add_history(comando);
		else
			exit(1);
	}
	return (0);
}