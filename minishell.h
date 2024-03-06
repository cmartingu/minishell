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
# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_fileobject
{
	char				*filename;
	int					heredoc;
	struct s_fileobject	*next;
}						t_fileobject;

typedef struct s_process
{
	char				**command;
	t_fileobject		*infile;
	t_fileobject		*outfile;
	struct s_process	*next;
}						t_process;

typedef struct s_pipex
{
	char	**c_env;
	int		**pipes;
	int		*childs;

}	t_pipex;

typedef struct s_auxiliar
{
	int					i;
	int					j;
	char				*name_var;
}						t_auxiliar;

size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			token_quant(char *cmd);
int			pipes_quant(char **tokens);
int			has_quot(char *cmd);
int			no_quot_tam(char *cmd, char **copy_env);
int			add_expansion(char *cmd, int *i, char **copy_env);
int			enviroment_sustitution(char *name_var, char **copy_env, \
int *iter, int cant_iter);
int			end_quotation(char **cmd, char quot);
int			contador_comillas(char *comando);
int			add_expansion(char *cmd, int *i, char **copy_env);
int			enviroment_sustitution(char *name_var, char **copy_env, \
int *iter, int cant_iter);
char		*ft_strdup(const char *s1);
char		**save_tokens(int tam, char **cmd);
char		*next_token(char **cmd);
char		*save_word_case(char **cmd);
char		*final_command(char *cmd, int tam, char **copy_env);
char		*skip_places(int i, char **cmd);
void		command_quot(char *cmd, char **aux, char **copy_env);
void		quant_aux(char **cmd, int *quant, int *i);
void		ctrl_C_handler(int sig);
void		ctrl_bar_handler(int sig);
void		add_process_back(t_process *proceso, t_process *proceso2);
void		ft_realloc_doble(t_process *proceso, char *str, int tam);
void		add_infile(t_process *proceso, char *inf, int flag);
void		add_outfile(t_process *proceso, char *outf, int flag);
void		add_cmd(t_process *proceso, char *cmd, int cmd_quant);
void		free_arr(char ***arr);
void		delete_quotation(char **cmd, char **copy_env);
void		delete_all_quot(t_process *process, char **copy_env);
void		count_quotation(char **cmd, int *i, char quot);
void		expansion_print(char *cmd, t_auxiliar *aux, \
char **final, char **cp_env);
void		save_expansion(char **aux, int *j, char **copy_env, char *name_var);
void		create_process(t_process *proceso, char **tok, int *i, int *qua);
void		save_final_quot(char **aux, char *cmd, int *i, int *j);
t_process	*tokenization_string(char *cmd, char **copy_env);
void		char_exc(char **cmd, int *quant, int *i);
t_process	*procesos(int nb, char **tokens);
extern void	rl_clear_history(void);
extern void	rl_replace_line(const char *b, int s);

#endif
