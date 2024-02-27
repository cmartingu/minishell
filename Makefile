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
SRC =	parseo/ctrl_handlers.c	\
		parseo/funciones_lib.c	\
		parseo/token_save.c	\
		parseo/add_process.c	\
		parseo/quotation_delete_aux.c	\
		parseo/token_quantification.c	\
		parseo/process_creation.c	\
		parseo/quotation_delete.c	\
		minishell.c
OBJ = $(SRC:.c=.o)
CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -L/Users/carlos-m/.brew/opt/readline/lib
LDLIBS := -I/Users/carlos-m/.brew/opt/readline/include -lreadline
REMOVE = rm -f
CC := cc
#ESTO COMPILA BIEN MIGUEL: cc pruebas.c -o tu_programa -I/Users/mllamas-/.brew/include -L/Users/mllamas-/.brew/lib -lreadline
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all
