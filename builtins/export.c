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

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s,%d\n", arr[i], i);
		i++;
	}
	printf("\n");
}

void	free_arr(char **arr)
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*sol;

	len = ft_strlen(s1);
	sol = malloc(len + 1);
	if (!sol)
		return (0);
	sol[len] = '\0';
	while (len--)
		sol[len] = s1[len];
	return (sol);
}

int	ft_isalpha(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
		return (1);
	else if ((c >= 48) && (c <= 57))
		return (1);
	else
		return (0);
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
	free_arr(old);
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
	int	pos;
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

/*int main(int argc, char **argv, char **env)
{
	char **copyEnv;
	char *strings[] = {"export",  NULL};
	copyEnv = copy_array(env);
	copyEnv = do_export(strings, copyEnv);
	
}*/
