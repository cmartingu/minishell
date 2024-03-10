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

char	**copy_array(char **old)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (old[len])
		len++;
	new = malloc((len + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	check_export(const char *str)
{
	int	equal;

	equal = 0;
	if (!ft_isalpha(*str))
		return (1);
	str++;
	while (*str != '\0')
	{
		if (*str == '=')
			equal = 1;
		else if (!ft_isalnum(*str))
			return (1);
		str++;
	}
	if (equal == 1)
		return (0);
	return (2);
}

void	insert_str(char ***copy_env, char *str)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while ((*copy_env)[len])
		len++;
	new = malloc((len + 2) * sizeof(char *));
	if (new == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup((*copy_env)[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free_array((*copy_env));
	(*copy_env) = new;
}

void	do_export(char **comando, char ***copyEnv)
{
	int	i;

	i = -1;
	if (comando[1] == NULL)
	{
		while ((*copyEnv)[i++] != NULL)
			printf("declare -x %s\n", (*copyEnv)[i]);
	}
	else
	{
		i = 1;
		while (comando[i] != NULL)
		{
			if (check_export(comando[i]) == 0)
				insert_str(copyEnv, comando[i]);
			else if (check_export(comando[i]) == 1)
			{
				write(2, "export: not an indentifier: ", 28);
				ft_putstr_fd(ft_strjoin(comando[i], "\n"), 2);
			}
			i++;
		}
	}
}
