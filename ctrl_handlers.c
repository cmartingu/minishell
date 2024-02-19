#include "minishell.c"

void	ctrl_C_handler(int sig)
{
	printf("\n");
	rl_on_new_line(); // Prepara readline para recibir una nueva línea
	rl_replace_line("", 0); // Limpia el buffer de la línea actual en readline
	rl_redisplay(); // Vuelve a mostrar el prompt
}

void	ctrl_bar_handler(int sig)
{
	return;
}