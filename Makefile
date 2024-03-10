# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 12:19:21 by carlos-m          #+#    #+#              #
#    Updated: 2024/02/20 12:19:22 by carlos-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
UNAME_S := $(USER)
SRC =	parseo/ctrl_handlers.c	\
		parseo/funciones_aux.c	\
		parseo/token_save.c	\
		parseo/add_process.c	\
		parseo/quotation_delete_aux.c	\
		parseo/token_quantification.c	\
		parseo/process_creation.c	\
		parseo/quotation_delete.c	\
		parseo/expansion.c	\
		builtins/cd.c  \
		builtins/echo.c  \
		builtins/env.c  \
		builtins/exit.c  \
		builtins/export.c  \
		builtins/pwd.c  \
		builtins/unset.c \
		executor/ejecutar.c	\
		executor/path.c	\
		executor/pipex.c	\
		executor/one_process.c	\
		executor/more_process.c	\
		checkfiles/check_outfiles.c\
		checkfiles/check_infiles.c \
		checkfiles/check_heredocs.c \
		get_next_line/get_next_line.c	\
		get_next_line/get_next_line_utils.c	\
		printea_procesos.c	\
		minishell.c
OBJ = $(SRC:.c=.o)
CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -L/Users/$(UNAME_S)/.brew/opt/readline/lib
LDLIBS := -I/Users/$(UNAME_S)/.brew/opt/readline/include -lreadline
REMOVE = rm -f
CC := cc
#ESTO COMPILA BIEN MIGUEL: cc pruebas.c -o tu_programa -I/Users/mllamas-/.brew/include -L/Users/mllamas-/.brew/lib -lreadline
all: $(NAME)

$(NAME): $(OBJ) Libft/libft.a
	@echo ".....Making Minishell....."
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS) Libft/libft.a

%.o: %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

Libft/libft.a:
	@echo ".....Making Libft...."
	@make -C Libft/

clean:
	@$(REMOVE) $(OBJ)
	@make -C Libft/ fclean

fclean: clean
	@$(REMOVE) $(NAME)

re: fclean all
