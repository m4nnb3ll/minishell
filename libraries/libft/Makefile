NAME := libft.a

CC := cc
CFLAGS := -Wall -Werror -Wextra

SRCS := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	   ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	   ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
	   ft_strdup.c ft_substr.c ft_strjoin.c ft_strjoin_f.c ft_strjoin_with.c ft_strjoin_with_f.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_free_char.c ft_strs_len.c ft_strs_arr_len.c \
	   ft_atoi_base.c ft_isspace.c

SRCS_BONUS := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			 ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			 ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS := $(SRCS:.c=.o)

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

INCLUDE_DIR := "../../include"

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

all: $(NAME) bonus

$(NAME): $(OBJS)
	@ar -rcs $@ $^

bonus: $(OBJS) $(OBJS_BONUS)
	@ar -rcs $(NAME) $^

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
