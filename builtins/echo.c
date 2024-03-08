/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:10:59 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 11:11:00 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_echo(char **command)
{
	int	i;
	int	n_all;
	int	j;

	i = 0;
	n_all = 1;
	j = 1;
	if (command[1] && command[1][0] == '-')
	{
		while (command[1][j])
		{
			if (command[1][j] != 'n')
			{
				n_all = 0;
				break ;
			}
			j++;
		}
	}
	else
		n_all = 0;
	if (n_all)
		i = 1;
	while (command[i++])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
	}
	if (!n_all)
		printf("\n");
}
