/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:17:01 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/05 11:17:02 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_alnumdeverdad(char *str)
{
	int	i;

	if (str[0] == '\0')
	{
		printf("Error: Numeric argument required\n");
		exit(255);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			printf("Error: Numeric argument required\n");
			exit(255);
		}
		i++;
	}
}

void	do_exit(char **comando)
{
	if (comando[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (comando[2] != NULL)
	{
		printf("Error: too many arguments\n");
		exit(1);
	}
	is_alnumdeverdad(comando[1]);
	exit(ft_atoi(comando[1]));
}
