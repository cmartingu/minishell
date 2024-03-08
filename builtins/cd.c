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


void	do_cd(char **command, char **copyEnv)
{
	int		i;
	char	*home;
	char	*aux;

	i = 0;
	home = NULL;
	if (!(command[1]) || (command[1][0] == '~' && command[1][1] == '\0'))
	{
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
		{
			perror("Minishell");
		}
	}
	else if (command[1][0] == '~' && command[1][1] != '\0')
	{
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
		if (chdir(ft_strjoin(home, aux)))
			perror("Minishell");
	}
	else
	{
		if (chdir(command[1]) != 0)
		{
			perror("Minishell");
		}
	}
}