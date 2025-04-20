NAME        = minishell
TEST_NAME	= test
CC          = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I/usr/local/opt/readline/include -g


LIBFT_PATH  = ./lib/libft
PRINTF_PATH = ./lib/ft_printf
GNL_PATH    = ./lib/gnl

LIBRARIES   =  -L$(LIBFT_PATH) -lft \
               -L$(PRINTF_PATH) -lftprintf \
               -L$(GNL_PATH) -lgnl \
               -lreadline -lhistory -lcurses \
               -ldl -pthread -lm


SRC_DIR     = src
SRC_FILES   =	main.c \
				signal.c \
				terminal_init.c \
				parsing/tokenizer.c \
				parsing/quote_and_meta_utils.c \
				parsing/token_counter.c \
				parsing/parsing_utils.c \
				parsing/token_splitter.c \
				parsing/token_add.c \
				parsing/token_del.c \
				parsing/quote_seperation.c \
				parsing/input_checking.c \
				parsing/between_token_op.c \
				parsing/expand_str.c \
				parsing/here_request.c \
				parsing/segment_operation.c \
				execution/execute_command.c \
				execution/path_resolver.c \
				utils.c \
				builtins/echo.c \
				execution/builtins.c \
				builtins/pwd.c \
				builtins/exit.c \
				builtins/cd.c \
				builtins/env.c \
				builtins/unset.c \
				builtins/export_utils.c \
				builtins/export_utils2.c \
				builtins/export.c \
				builtins/cd_utils.c \
				parsing/expand.c \
				parsing/expand_utils.c \
				parsing/expand_utils2.c \
				execution/redirection.c \
				execution/redirection_utils.c \
				execution/redirection_heredoc.c \


SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
TEST_SRCS	= $(filter-out $(SRC_DIR)/main.c , $(SRCS))
TEST_SRCS	+= tests/main.c
TEST_SRCS	+= tests/parsing_test.c
OBJS        = $(SRCS:.c=.o)
TEST_OBJS	= $(TEST_SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) > /dev/null
	@echo "\033[1;32m✔ Compiled: $<\033[0m"

$(NAME): libft ftprintf gnl $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null

ftprintf:
	@make -C $(PRINTF_PATH)

libft:
	@make -C $(LIBFT_PATH)

gnl:
	@make -C $(GNL_PATH)

clean:
	@rm -f $(OBJS) > /dev/null
	@make -C $(LIBFT_PATH) clean > /dev/null
	@make -C $(PRINTF_PATH) clean > /dev/null
	@make -C $(GNL_PATH) clean > /dev/null
	@rm -f $(TEST_OBJS) > /dev/null

fclean: clean
	@rm -f $(NAME) > /dev/null
	@rm -f $(TEST_NAME) > /dev/null
	@make -C $(LIBFT_PATH) fclean > /dev/null
	@make -C $(PRINTF_PATH) fclean > /dev/null
	@make -C $(GNL_PATH) fclean > /dev/null
	@echo "\033[1;33m Fully cleaned $(NAME)!\033[0m"

re: fclean all

all: $(NAME)

test: libft ftprintf gnl $(TEST_OBJS)
	@$(CC) $(TEST_OBJS) $(LIBRARIES) -o $(TEST_NAME) > /dev/null
	@make clean


.PHONY: all clean fclean re libft gnl tests
