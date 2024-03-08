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


void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**insert_str(char **old, char *str)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (old[len])
		len++;
	new = malloc((len + 2) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = str;
	new[i + 1] = NULL;
	free_array(old);
	return (new);
}

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

char	**do_export(char **comando, char **copyEnv)
{
	int	i;

	i = 0;
	if (comando[1] == NULL)
	{
		while (copyEnv[i] != NULL)
		{
			printf("declare -x %s\n", copyEnv[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		while (comando[i])
		{
			if (check_export(comando[i]) == 0)
			{
				copyEnv = insert_str(copyEnv, comando[i]);
				printf("Valido: %s\n", comando[i]);
			}
			else if (check_export(comando[i]) == 1)
				printf("Error: %s\n", comando[i]);
			else
				printf("Invalido: %s\n", comando[i]);
			i++;
		}
	}
	return (copyEnv);
}
