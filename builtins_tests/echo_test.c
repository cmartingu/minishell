/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:10:59 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 11:11:00 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <curses.h>

void	do_echo(char **command)
{
	int	i;
	int	n_all;
	int	j;

	i = 0;
	n_all = 1;
	j = 1;
	if (command[1] && command[1][0] == '-')
	{
		while (command[1][j])
		{
			if (command[1][j] != 'n')
			{
				n_all = 0;
				break ;
			}
			j++;
		}
	}
	else
		n_all = 0;
	if (n_all)
		i = 1;
	while (command[i++])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
	}
	if (!n_all)
		printf("\n");
}

void	decide(char **command)
{
	if (strncmp(command[0], "export", ft_strlen(command[0])) == 0)
		do_export(command);
	else if (strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		do_echo(command);
	else if (strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
		do_pwd(command);
	else if (strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
		do_cd(command);
	else if (strncmp(command[0], "unset", ft_strlen(command[0])) == 0)
		do_unset(command);
	else if (strncmp(command[0], "env", ft_strlen(command[0])) == 0)
		do_env(command);
	else if (strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		do_exit(command);
	else
		printf("Command to execve\n");
}

/*int	main(void)
{
	char *strings[] = {"echo", NULL};
	do_echo(strings);
}*/
