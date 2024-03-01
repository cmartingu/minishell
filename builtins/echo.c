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

void    do_echo(char **command)
{
    int i = 0;
    int n_all = 1;
    int j = 1;
    if (command[1] && command[1][0] == '-') {
        while (command[1][j]) {
            if (command[1][j] != 'n') {
                n_all = 0;
                break;
            }
            j++;
        }
    }
    else
        n_all = 0;
    if (n_all)
        i = 1;
    while (command[i++]) {
        printf("%s", command[i]);
        if (command[i + 1])
            printf(" ");
    }
    if (!n_all)
        printf("\n");
}

void decide(char **command) {
    if (strncmp(command[0], "export", ft_strlen(command[0])) == 0) {
        do_export(command);
    } else if (strncmp(command[0], "echo", ft_strlen(command[0])) == 0) {
        do_echo(command);
    } else if (strncmp(command[0], "pwd", ft_strlen(command[0])) == 0) {
        do_pwd(command);
    } else if (strncmp(command[0], "cd", ft_strlen(command[0])) == 0) {
        do_cd(command);
    } else if (strncmp(command[0], "unset", ft_strlen(command[0])) == 0) {
        do_unset(command);
    } else if (strncmp(command[0], "env", ft_strlen(command[0])) == 0) {
        do_env(command);
    } else if (strncmp(command[0], "exit", ft_strlen(command[0])) == 0) {
        do_exit(command);
    } else {
        printf("Command to execve\n");
    }
}

int main(void)
{
    char *strings[] = {"echo", NULL};
    do_echo(strings);
}