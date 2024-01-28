NAME = minishell

SOURCES =	minishell.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS := -Wall -Wextra -Werror
REMOVE = rm -f
CC := cc

all: $(NAME)

$(NAME): $(OBJECTS) Libft/libft.a
	$(CC) $(OBJECTS) -lreadline -o $(NAME) Libft/libft.a

Libft/libft.a:
	make -C Libft/

clean:
	$(REMOVE) $(OBJECTS)
	make -C Libft/ fclean

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all