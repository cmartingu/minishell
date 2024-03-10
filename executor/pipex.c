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
	pipes = malloc((quant + 1) * sizeof(int *));
	if (!pipes)
		perror("Minishell");
	pipes[quant] = NULL;
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

t_pipex	*ini_pipex(int process_num, char ***envp, t_process *proceso)
{
	t_pipex	*pipexx;

	pipexx = malloc(sizeof(t_pipex));
	if (!pipexx)
		perror("Minishell");
	pipexx->pipes = create_pipes(process_num - 1);
	pipexx->childs = malloc(process_num * sizeof(int));
	if (!pipexx->childs)
		perror("Minishell");
	pipexx->c_env = envp;
	pipexx->last_inf = check_infiles(proceso);
	if (pipexx->last_inf != -2)
		pipexx->last_out = check_outfiles(proceso);
	else
		pipexx->last_out = -1;
	return (pipexx);
}

t_macro_pipex	*ini_macro_pipex(int process_num, char ***envp)
{
	t_macro_pipex	*pipexx;

	pipexx = malloc(sizeof(t_macro_pipex));
	if (!pipexx)
		perror("Minishell");
	pipexx->pipes = create_pipes(process_num - 1);
	pipexx->childs = malloc(process_num * sizeof(int));
	if (!pipexx->childs)
		perror("Minishell");
	pipexx->num_process = process_num;
	pipexx->c_env = envp;
	return (pipexx);
}

void	close_pipes(t_macro_pipex *pipexx, int process_num)
{
	int	i;

	i = 0;
	while (i < (process_num - 1))
	{
		close((pipexx->pipes)[i][0]);
		close((pipexx->pipes)[i][1]);
		i++;
	}
}
