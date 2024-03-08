/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:19:36 by carlos-m          #+#    #+#             */
/*   Updated: 2024/01/21 11:19:37 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**create_pipes(int quant)
{
	int	**pipes;

	if (quant == 0)
		return (NULL);
	pipes = malloc(quant * sizeof(int *));
	if (!pipes)
		perror("Minishell");
	while (quant--)
	{
		pipes[quant] = malloc(2);
		if (pipe(pipes[quant]) == -1)
		{
			write(1, "Error, pipe error\n", 18);
			exit(1);
		}
	}
	return (pipes);
}

/*void	close_pipes(t_pipex *pipexx)
{
	int	i;

	i = 0;
	while (i < pipexx->tam)
	{
		close((pipexx->pipes)[i][0]);
		close((pipexx->pipes)[i][1]);
		i++;
	}
}

void	middle_childs(t_pipex *pipexx)
{
	char	*path;
	int		aux_arg;
	int		i;
	int		j;

	i = 3;
	j = 1;
	aux_arg = pipexx->argc;
	while (aux_arg > 5)
	{
		aux_arg--;
		(pipexx->childs)[j] = fork();
		if ((pipexx->childs)[j] == 0)
		{
			dup2((pipexx->pipes)[aux_arg - 4][0], STDIN_FILENO);
			dup2((pipexx->pipes)[aux_arg - 5][1], STDOUT_FILENO);
			close_pipes(pipexx);
			path = find_path(pipexx->env, (pipexx->argv)[i]);
			ejecutar(pipexx->env, path, (pipexx->argv)[i]);
			exit(127);
		}
		i++;
		j++;
	}
}

t_pipex	*ini_pipex(int arg, char **envp, char **argvv)
{
	t_pipex	*pipexx;

	pipexx = malloc(sizeof(t_pipex));
	pipexx = malloc(sizeof(t_pipex));
	pipexx->tam = arg - 4;
	pipexx->pipes = create_pipes(pipexx->tam);
	pipexx->env = envp;
	pipexx->argc = arg;
	pipexx->argv = argvv;
	pipexx->childs = malloc((arg - 3) * sizeof(int));
	return (pipexx);
}

int	main(int arg, char *argvv[], char *envp[])
{
	int		status;
	int		i;
	t_pipex	*pipexx;

	if (arg < 5)
	{
		write(1, "Error, you have to put at least 2 commands\n", 43);
		exit(1);
	}
	pipexx = ini_pipex(arg, envp, argvv);
	(pipexx->childs)[0] = fork();
	if ((pipexx->childs)[0] == 0)
		first_process(pipexx);
	middle_childs(pipexx);
	(pipexx->childs)[pipexx->tam] = fork();
	if ((pipexx->childs)[arg - 4] == 0)
		last_process(pipexx);
	close_pipes(pipexx);
	i = 0;
	while (i <= pipexx->tam)
	{
		waitpid((pipexx->childs)[i], &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}*/
