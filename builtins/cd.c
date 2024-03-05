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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*aux1;
	unsigned char	*aux2;

	aux1 = (unsigned char *)s1;
	aux2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((aux1[i] == aux2[i]) && (i < (n - 1)))
	{
		if (aux1[i] == '\0' && aux2[i] == '\0')
			return (0);
		i++;
	}
	return (aux1[i] - aux2[i]);
}

void	do_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf != NULL)
	{
		printf("%s\n", buf);
		free(buf);
	}
	else
	{
		perror("Minishell error:");
	}
}

void	do_cd(char **command, char **copyEnv)
{
	int		i;
	char	*home;

	i = 0;
	do_pwd();
	if (!(command[1]) || (command[1][0] == '~' && command[1][1] == '\0'))
	{
		while (copyEnv[i] != NULL)
		{
			if (strncmp(copyEnv[i], "HOME=", 5) == 0)
			{
				home = copyEnv[i] + 5;
				break ;
			}
			i++;
		}
		printf("Path Home: %s\n", home);
		if (home && chdir(home) != 0)
		{
			perror("Minishell");
		}
	}
	else
	{
		printf("Path Comand: %s\n", command[1]);
		if (chdir(command[1]) != 0)
		{
			perror("Minishell");
		}
	}
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

/*int main(int argc, char **argv, char **env)
{
	char	**copyEnv;
	char	*strings[];

	strings = {"cd", "~", NULL};
	copyEnv = copy_array(env);
	do_cd(strings, copyEnv);
	do_pwd();
}*/
