#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "Libft/libft.h"
#include <signal.h>

int main(void)
{
	char	*comando;

	while (1)
	{
		comando = readline("minishell>");
		if (comando && *comando)
        	add_history(comando);
		if (ft_strncmp(comando, "history -c", 10) == 0)
			rl_clear_history();
		else if (ft_strncmp(comando, "exit", 4) == 0)
		{
			printf("exit\n");
			exit(0);
		}
	}
	return (0);
}