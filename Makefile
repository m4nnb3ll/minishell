NAME		:= minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra

BUILTINS	:=	builtins/cd.c \
				builtins/echo.c \
				builtins/env_utils.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export.c \
				builtins/pwd.c \
				builtins/unset.c

CLEANING	:=	cleaning/ft_clean_ms.c

EXEC		:=	exec/error_msg.c \
				exec/exec_builtin.c \
				exec/exec_redirect.c \
				exec/exec_utils.c \
				exec/exec.c \
				exec/exist_check.c \
				exec/ft_exec_simple_cmd.c \
				exec/ft_get_path.c \
				exec/init_tree.c

EXPANDER	:=	expander/ft_asterisker.c \
				expander/ft_clean_empty_strs.c \
				expander/ft_expand_utils.c \
				expander/ft_expand.c \
				expander/ft_expander_split.c \
				expander/ft_globber_utils.c \
				expander/ft_globber.c \
				expander/ft_strip_quotes.c \
				expander/heredoc_expander.c

PARSING		:=	parsing/parser_clear.c \
				parsing/parser_err.c \
				parsing/parser_helpers.c \
				parsing/parser_nodes.c \
				parsing/parser_utils.c \
				parsing/parser.c

TOKENIZING	:=	tokenizing/tokenizer_appenders.c \
				tokenizing/tokenizer_handlers.c \
				tokenizing/tokenizer_lst.c \
				tokenizing/tokenizer_utils.c \
				tokenizing/tokenizer.c

SRCS		:=	$(BUILTINS)\
				$(CLEANING)\
				$(EXEC)\
				$(EXPANDER)\
				$(PARSING)\
				$(TOKENIZING)\
				main.c main_signals.c

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH:=	/goinfre/homebrew/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE_PATH)/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
