# Minishell 🖥️

Minishell es una implementación en C de un shell básico similar al de Unix.
Este proyecto simula el comportamiento de un shell, manejando comandos, redirección de entrada/salida, ejecución de programas y control de procesos, sin depender de bibliotecas externas. 🐚

## Funcionalidades ✨

- **Ejecución de comandos**: El shell puede ejecutar comandos internos (como `cd`, `exit`, `echo`, entre otros) y también ejecutar comandos externos (como cualquier programa en el sistema). 🖥️
- **Redirección de entrada y salida**: Soporta redirección de entrada (`<` o `<<`) y salida (`>` o `>>`). 🔄
- **Pipes**: Permite encadenar varios comandos con pipes (`|`), donde la salida de un comando se pasa como entrada al siguiente. 🔗
- **Manejo de señales**: Maneja las señales `SIGINT` (Ctrl+C) y `SIGQUIT` (Ctrl+\), permitiendo controlar el flujo del shell durante la ejecución de los procesos. ⚠️
- **Control de procesos**: Utiliza `fork()` para crear nuevos procesos y `waitpid()` para esperar a que terminen. 🕰️

## Instalación y uso 🚀
```bash
make
```
Para usarlo ejecuta el siguiente comando:
```bash
../minishell
```
Ahora podrás usarlo como una terminal bash, por ejemplo:
```bash
$ ./minishell
minishell> echo "Hola Mundo"
Hola Mundo
minishell> ls
file1.txt  file2.txt
minishell> cd /home/user
minishell> exit
```
