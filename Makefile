NAME=minishell

SRC_DIR=src
OBJ_DIR=obj
SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))


CC=cc
CFLAGS= -Wall -Wextra -Werror -g
LDFLAGS= -lreadline -lhistory

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
INC=-I./include -I./$(LIBFT_DIR)/include


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all