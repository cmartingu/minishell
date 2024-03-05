/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:17:01 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 11:17:02 by carlos-m         ###   ########.fr       */
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

void	do_unset(char *command, char **env)
{
	char	*var;

	var = ft_substr(comando, 6, ft_strlen(comando) - 6);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, var, ft_strlen(var)) == 0 && \
		(*env)[ft_strlen(var)] == '=')
		{
			while (*env != NULL)
			{
				*env = *(env + 1);
				env++;
			}
			break ;
		}
		env++;
	}
}
