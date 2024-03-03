#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para malloc, free
#include <unistd.h>     // Para read, write, close, fork, execve, chdir, getcwd, dup, dup2, pipe, access, unlink, isatty, ttyname, ttyslot
#include <fcntl.h>      // Para open
#include <sys/wait.h>   // Para wait, waitpid, wait3, wait4
#include <sys/types.h> // 
#include <sys/resource.h>
#include <sys/stat.h>   // Para stat, fstat, lstat
#include <signal.h>     // Para signal, kill, sigaction
#include <dirent.h>     // Para opendir, readdir, closedir
#include <string.h>     // Para strerror
#include <termios.h>    // Para tcsetattr, tcgetattr
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

void 	do_pwd()
{
    char	*buf;
	
	buf = getcwd(NULL, 0); 
    if (buf != NULL) {
        printf("%s\n", buf); 
        free(buf);
    } else {
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
				break;
			}
			i++;
		}
		printf("Path Home: %s\n", home);
		if (home && chdir(home) != 0) {
    		perror("Minishell");
    	}
	}
	else
	{
		printf("Path Comand: %s\n", command[1]);
		if (chdir(command[1]) != 0) {
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

char 	**copyArray(char **old)
{
	int	len;
	int	i;
	char	**new;

	len = 0;
	while (old[len])
		len++;
	new = malloc((len + 1) * sizeof(char *));
	if (new == NULL) 
		return NULL;
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int main(int argc, char **argv, char **env)
{
	char **copyEnv;
	char *strings[] = {"cd", "~", NULL};
	copyEnv = copyArray(env);
	do_cd(strings, copyEnv);
	do_pwd();
}