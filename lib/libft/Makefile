# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:59:09 by blohrer           #+#    #+#              #
#    Updated: 2025/04/09 09:27:49 by blohrer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror


SRC		=	ft_isdigit.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_split.c \
			ft_strncmp.c \
			ft_strmapi.c \
			ft_isprint.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strcat.c \

BONUS	=	ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c \

OBJ 	= $(SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS:.c=.o)
	@ar -r $(NAME) $? > /dev/null

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ) > /dev/null

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null


clean:
	@rm -f $(OBJ) $(BONUS:.c=.o) > /dev/null


fclean: clean
	@rm -f $(NAME) > /dev/null


re: fclean all

.PHONY: all clean fclean re bonus
