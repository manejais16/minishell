# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 10:58:28 by blohrer           #+#    #+#              #
#    Updated: 2024/11/14 08:20:48 by blohrer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
AR = ar

CFILES =	ft_putchar.c \
			ft_putstr.c \
			ft_putnbr_fd.c \
			ft_puthex.c \
			ft_put_unsigned.c \
			ft_put_pointer.c \
			ft_printf.c \

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(AR) rcs $(NAME) $(OFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME) $(OBFILES)

re: fclean all

.PHONY: all clean fclean re
