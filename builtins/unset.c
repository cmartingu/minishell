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

void	do_unset(char *command, char **env)
{
	char	*var;

	var = ft_substr(command, 6, ft_strlen(command) - 6);
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
