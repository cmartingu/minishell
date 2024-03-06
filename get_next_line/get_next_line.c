/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:17:12 by carlos-m          #+#    #+#             */
/*   Updated: 2023/11/29 11:17:14 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*nl_exception(char **buff)
{
	char	*sol;
	int		cont;
	char	*aux_final_buff;

	sol = NULL;
	cont = 0;
	while ((*buff)[cont] != '\n')
	{
		sol = ft_realloc(sol, cont, (*buff)[cont]);
		cont++;
	}
	sol = ft_realloc(sol, cont, (*buff)[cont]);
	if ((*buff)[cont + 1])
		aux_final_buff = ft_strdup(ft_strchr(*buff, '\n') + 1);
	else
		return (free(*buff), *buff = NULL, sol);
	free(*buff);
	*buff = aux_final_buff;
	return (sol);
}

char	*ft_has_jl(char **buff, char **sol, int aux_cont)
{
	char	*aux_final_buff;

	aux_final_buff = NULL;
	if ((*buff)[aux_cont + 1])
		aux_final_buff = ft_strdup(&(*buff)[aux_cont + 1]);
	free(*buff);
	*buff = aux_final_buff;
	return (*sol);
}

char	*ft_read(int numbytes, char **buff, char **sol, int fd)
{
	int		aux_cont;
	int		cont;

	cont = ft_strlen(*sol);
	while (numbytes > 0)
	{
		aux_cont = 0;
		while ((*buff)[aux_cont])
		{
			*sol = ft_realloc(*sol, cont, (*buff)[aux_cont]);
			if ((*buff)[aux_cont] == '\n')
				return (ft_has_jl(&(*buff), &(*sol), aux_cont));
			cont++;
			aux_cont++;
		}
		free(*buff);
		*buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!(*buff))
			return (NULL);
		numbytes = read(fd, *buff, BUFFER_SIZE);
	}
	free(*buff);
	*buff = NULL;
	return (*sol);
}

char	*add_buff(char **buff)
{
	char	*sol;

	sol = ft_strdup(*buff);
	free(*buff);
	*buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	return (sol);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*sol;
	int			numbytes;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!buff)
	{
		buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		sol = NULL;
	}
	else
	{
		if (!ft_strchr(buff, '\n'))
			sol = add_buff(&buff);
		else
			return (nl_exception(&buff));
	}
	numbytes = read(fd, buff, BUFFER_SIZE);
	if (numbytes == -1)
		return (free(buff), free(sol), buff = NULL, NULL);
	if (numbytes <= 0)
		return (free(buff), buff = NULL, sol);
	return (ft_read(numbytes, &buff, &sol, fd));
}
