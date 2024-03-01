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

void 	do_pwd()
{
    char	*buf;
	
	buf = getcwd(NULL, 0); // Solicita a getcwd que asigne un búfer
    if (buf != NULL) {
        printf("%s\n", buf); // Imprime el directorio actual
        free(buf); // Libera la memoria asignada a buf
    } else {
        perror("Minishell error:"); // Maneja el error
    }
}
