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

void do_unset(char *command, char **env)
{
	char *var;

	var = ft_substr(comando, 6, ft_strlen(comando) - 6);
 	while (*env != NULL) {
        if (ft_strncmp(*env, var, ft_strlen(var)) == 0 && (*env)[ft_strlen(var)] == '=') {
            while (*env != NULL) {
                *env = *(env + 1);
                env++;
            }
            break;
        }
        env++;
    }
}