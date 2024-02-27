/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:18:46 by carlos-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:18:50 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_fileobject
{
	char				*filename;
	struct s_fileobject	*next;
}						t_fileobject;

typedef struct s_process
{
	char				**command;
	t_fileobject		*infile;
	t_fileobject		*outfile;
	struct s_process	*next;
}						t_process;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
char		**save_tokens(int tam, char **cmd);
char		*next_token(char **cmd);
char		*save_word_case(char **cmd);
int			token_quant(char *cmd);
void		quant_aux(char **cmd, int *quant, int *i);
void		ctrl_C_handler(int sig);
void		ctrl_bar_handler(int sig);
void		add_process_back(t_process *proceso, t_process *proceso2);
void		ft_realloc_doble(t_process *proceso, char *str, int tam);
int			pipes_quant(char **tokens);
void		add_infile(t_process *proceso, char *inf);
void		add_outfile(t_process *proceso, char *outf);
void		free_arr(char ***arr);
void		add_cmd(t_process *proceso, char *cmd, int cmd_quant);
void		delete_quotation(char **cmd);
void		count_quotation(char **cmd, int *i, char quot);
void		create_process(t_process *proceso, char **tok, int *i, int *qua);
t_process	*procesos(int nb, char **tokens);
extern void	rl_clear_history(void);
extern void	rl_replace_line(const char *b, int s);

#endif
