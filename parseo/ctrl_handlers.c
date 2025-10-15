/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:19:30 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:19:31 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c_handler(int sig)
{
	(void) sig;
	if (g_sig_handler == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		g_sig_handler = 0;
}

void	ctrl_bar_handler(int sig)
{
	(void) sig;
	return ;
}

int	ini_signals(void)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	if (signal(SIGINT, ctrl_c_handler) == SIG_ERR || \
	signal(SIGQUIT, ctrl_bar_handler) == SIG_ERR)
	{
		printf("Error al establecer el manejador de SIGINT\n");
		return (-1);
	}
	return (0);
}
