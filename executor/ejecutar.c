/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ejecutar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:17:01 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 11:17:02 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ejecutar(char *envp[], char *path, char **comando)
{
	execve(path, comando, envp);
	write(2, "Error, comando no encontrado\n", 29);
	exit(127);
}
