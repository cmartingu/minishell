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

#include "../minishell.h"

void	do_unset(char **command, char **env)
{
	int	i;

	i = 1;
	while (command[i] != NULL)
	{
		while (*env != NULL)
		{
			if (ft_strncmp(*env, command[i], ft_strlen(command[i])) == 0 && \
			(*env)[ft_strlen(command[i])] == '=')
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
		i++;
	}

}
