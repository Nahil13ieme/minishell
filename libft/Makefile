NAME = libft.a
SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_realloc.c ft_isspace.c ft_strcmp.c \

BSOURCES = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(GREEN) Compilation de la LIBFT $(RESET)"
	@$(AR) -r $@ $?
	@echo "$(GREEN) Compilation Reussi $(RESET)"


bonus: $(OBJECTS) $(BOBJECTS)
	@$(AR) -r $(NAME) $?

%.o: %.c
	@$(CC) -c $(CFLAGS) $?

clean:
	@echo "$(RED) Clean de la LIBFT $(RESET)"
	@rm -f $(OBJECTS) $(BOBJECTS)
	@echo "$(RED) Clean terminer $(RESET)"
fclean: clean
	@echo "$(RED) Grand menage de la LIBFT $(RESET)"
	@rm -f $(NAME)
	@echo "$(RED) Grand menage terminer $(RESET)"


re: fclean all

.PHONY: all bonus clean fclean re
