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
#include <curses.h>     // o <termcap.h> para funciones tgetent, tgetflag, etc., dependiendo de la biblioteca de terminal utilizada

// Readline y History
#include <readline/readline.h> // Para readline
#include <readline/history.h>  // Para add_history

// Firmas de función

char *readline(const char *prompt);                      //Incluir un if (char == NULL) -> return; porque devuelve NULL si no lee nada.
void rl_clear_history(void);                             //No toma argumentos ni devuelve argumentos. Usarla siempre que se quiera limpiar el historial.
void rl_on_new_line(void);                               //Creo que se deberia hacer cuando hacer un printf o algo asi, que la siguiente aparezca en la linea siguiente.(Aunque si no hay salto de linea el shell pone el zsh despues de la linea)
void rl_replace_line(const char *text, int clear_undo);  //Sustituye lo recibido por readline por otro texto. Limpia el historial de deshacer si hay algo distinto a un 0 en clear undo (Ctrl -) sirve para ir hacia atras.
void rl_redisplay(void);                                 //Actualiza por pantalla el texto modificado por replace_line.
void add_history(const char *line);                      //Añade la linea de readline al historial.

int printf(const char *format, ...);                     //
void *malloc(size_t size);                               //
void free(void *ptr);                                    // 

ssize_t write(int fd, const void *buf, size_t count);    //
int access(const char *pathname, int mode);              //
int open(const char *pathname, int flags, ...);          //
ssize_t read(int fd, void *buf, size_t count);           //
int close(int fd);                                       //

pid_t fork(void);                                                        //
pid_t wait(int *status);                                                 //
pid_t waitpid(pid_t pid, int *status, int options);                      //
int wait3(int *status, int options, struct rusage *rusage);              //
int wait4(pid_t pid, int *status, int options, struct rusage *rusage);   //Es un waitpid pero con mas opciones. (Mirar opciones si es necesario, de momento no)

void (*signal(int sig, void (*func)(int)))(int);                                      //SIG_ERROR en caso de error
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);     //-1 en caso de error
int kill(pid_t pid, int sig);                                                         //-1 en caso de error
void exit(int status);                                                                //

char *getcwd(char *buf, size_t size);      //
int chdir(const char *path);               //

int stat(const char *path, struct stat *buf);    //
int lstat(const char *path, struct stat *buf);   //
int fstat(int fd, struct stat *buf);             //
int unlink(const char *pathname);                //

int execve(const char *filename, char *const argv[], char *const envp[]);      //
int dup(int oldfd);                                                            //
int dup2(int oldfd, int newfd);                                                //
int pipe(int pipefd[2]);                                                       //

DIR *opendir(const char *name);                //
struct dirent *readdir(DIR *dirp);             //
int closedir(DIR *dirp);                       //

char *strerror(int errnum);              //
void perror(const char *s);              //
int isatty(int fd);                      //
char *ttyname(int fd);                   //
int ttyslot(void);                       //

int ioctl(int fd, unsigned long request, ...);   //
char *getenv(const char *name);                  //

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);    //Lo usamos para que no escriba el CTRL + C
int tcgetattr(int fd, struct termios *termios_p);                                //"			"         "				"

int tgetent(char *bp, const char *name);                      //
int tgetflag(char *id);                                       //       
int tgetnum(char *id);                                        //
char *tgetstr(char *id, char **area);                         //
char *tgoto(const char *cap, int col, int row);               //
int tputs(const char *str, int affcnt, int (*putc)(int));     //


/*Flags en termios
Las "flags" en la estructura termios controlan varios aspectos del comportamiento del terminal. Están agrupadas en diferentes categorías: c_iflag (flags de modo de entrada), c_oflag (flags de modo de salida), c_cflag (flags de control), y c_lflag (flags de modo local). Algunas de las flags más comunes incluyen:

Modo de Entrada (c_iflag):

IGNBRK: Ignora las pausas (break conditions).
BRKINT: Interrumpe la entrada (y posiblemente la salida) si se detecta una pausa.
ICRNL: Convierte el retorno de carro a nueva línea en la entrada.
INLCR: Convierte nueva línea a retorno de carro en la entrada.
IXON: Habilita el control de flujo de salida con START/STOP.
Modo de Salida (c_oflag):

OPOST: Habilita el procesamiento de salida post.
ONLCR: Convierte nueva línea a retorno de carro-nueva línea en la salida.
Control (c_cflag):

CSIZE: Máscara de bits para tamaños de caracteres.
PARENB: Habilita la generación de paridad.
CSTOPB: Establece dos bits de stop.
Modo Local (c_lflag):

ECHO: Habilita el eco de entrada.
ICANON: Habilita el modo canónico.
ISIG: Habilita la captura de señales INTR, QUIT y SUSP.
ECHOE: Borra el carácter como error de backspace.
ECHOCTL: Ecoa los caracteres de control como ^char y ^? para DEL.

1	SIGHUP	23	SIGURG	45	SIGRTMIN+11
2	SIGINT	24	SIGXCPU	46	SIGRTMIN+12
3	SIGQUIT	25	SIGXFSZ	47	SIGRTMIN+13
4	SIGILL	26	SIGVTALRM	48	SIGRTMIN+14
5	SIGTRAP	27	SIGPROF	49	SIGRTMIN+15
6	SIGABRT	28	SIGWINCH	50	SIGRTMAX-14
7	SIGBUS	29	SIGIO	51	SIGRTMAX-13
8	SIGFPE	30	SIGPWR	52	SIGRTMAX-12
9	SIGKILL	31	SIGSYS	53	SIGRTMAX-11
10	SIGUSR1	32	SIGWAITING	54	SIGRTMAX-10
11	SIGSEGV	33	SIGLWP	55	SIGRTMAX-9
12	SIGUSR2	34	SIGRTMIN	56	SIGRTMAX-8
13	SIGPIPE	35	SIGRTMIN+1	57	SIGRTMAX-7
14	SIGALRM	36	SIGRTMIN+2	58	SIGRTMAX-6
15	SIGTERM	37	SIGRTMIN+3	59	SIGRTMAX-5
16	SIGSTKFLT	38	SIGRTMIN+4	60	SIGRTMAX-4
17	SIGCHLD	39	SIGRTMIN+5	61	SIGRTMAX-3
18	SIGCONT	40	SIGRTMIN+6	62	SIGRTMAX-2
19	SIGSTOP	41	SIGRTMIN+7	63	SIGRTMAX-1
20	SIGTSTP	42	SIGRTMIN+8	64	SIGRTMAX
21	SIGTTIN	43	SIGRTMIN+9		
22	SIGTTOU	44	SIGRTMIN+10	
