NAME        = minishell
CC          = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I/usr/local/opt/readline/include -g


LIBFT_PATH  = ./lib/libft
PRINTF_PATH = ./lib/ft_printf
GNL_PATH    = ./lib/gnl

LIBRARIES   =  -L$(LIBFT_PATH) -lft \
               -L$(PRINTF_PATH) -lftprintf \
               -L$(GNL_PATH) -lgnl \
               -L/usr/local/opt/readline/lib -lreadline -lhistory -lcurses \
               -ldl -pthread -lm


SRC_DIR     = src
SRC_FILES   =	main.c \
				signal.c \
				parsing/tokenizer.c \
				execution/execute_command.c \
				execution/path_resolver.c \
				utils.c \
				builtins/echo.c \
				execution/builtins.c \
				builtins/pwd.c \
				builtins/exit.c \
				builtins/cd.c \
				builtins/env.c \
				builtins/unset.c


SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "\033[1;32m✔ Compiled: $<\033[0m"

$(NAME): libft ftprintf gnl $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) -o $(NAME)

ftprintf:
	@make -C $(PRINTF_PATH)

libft:
	@make -C $(LIBFT_PATH)

gnl:
	@make -C $(GNL_PATH)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(PRINTF_PATH) clean
	@make -C $(GNL_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(PRINTF_PATH) fclean
	@make -C $(GNL_PATH) fclean
	@echo "\033[1;33m Fully cleaned $(NAME)!\033[0m"

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libft gnl
