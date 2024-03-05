# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 10:35:27 by carlos-m          #+#    #+#              #
#    Updated: 2023/10/05 19:01:30 by carlos-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

NAME_BONUS = .bonus

MONDONGO = ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c \
ft_atoi.c ft_isdigit.c ft_memmove.c ft_split.c ft_strlcpy.c ft_strtrim.c \
ft_bzero.c ft_isprint.c ft_memset.c ft_strchr.c ft_strlen.c ft_substr.c \
ft_calloc.c ft_itoa.c ft_putchar_fd.c ft_strdup.c ft_strmapi.c ft_tolower.c \
ft_isalnum.c ft_memchr.c ft_putendl_fd.c ft_striteri.c ft_strncmp.c ft_toupper.c \
ft_isalpha.c ft_memcmp.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c
OBJECTS = $(MONDONGO:.c=.o)

MONDONGO_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECTS_BONUS = $(MONDONGO_BONUS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

INCLUDE = libft.h

all: $(NAME)

$(NAME): $(OBJECTS) $(INCLUDE)
	ar -crs $(NAME) $(OBJECTS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJECTS) $(OBJECTS_BONUS) $(INCLUDE)
	ar -rcs $(NAME) $(OBJECTS) $(OBJECTS_BONUS)
	ar -rcs $(NAME_BONUS) $(OBJECTS) $(OBJECTS_BONUS)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
