/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:58:54 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 10:58:57 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_home(char **copyEnv)
{
	char	*home;
	int		i;

	home = NULL;
	i = 0;
	while (copyEnv[i] != NULL)
	{
		if (ft_strncmp(copyEnv[i], "HOME=", 5) == 0)
		{
			home = copyEnv[i] + 5;
			break ;
		}
		i++;
	}
	if (home && chdir(home) != 0)
		perror("Minishell");
}

void	change_subdirectory(char **command, char **copyEnv)
{
	char	*home;
	char	*aux;
	int		i;

	home = NULL;
	i = 0;
	while (copyEnv[i] != NULL)
	{
		if (ft_strncmp(copyEnv[i], "HOME=", 5) == 0)
		{
			home = copyEnv[i] + 5;
			break ;
		}
		i++;
	}
	aux = ft_strdup(command[1] + 1);
	if (chdir(ft_strjoin(home, aux)) != 0)
		perror("Minishell");
}

void	do_cd(char **command, char **copyEnv)
{
	if (!(command[1]) || ((command[1][0] == '~' || command[1][0] == '-')
		&& command[1][1] == '\0'))
		change_home(copyEnv);
	else if ((command[1][0] == '~' || command[1][0] == '-')
		&& command[1][1] != '\0')
		change_subdirectory(command, copyEnv);
	else
	{
		if (chdir(command[1]) != 0)
			perror("Minishell");
	}
}
