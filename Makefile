NAME=minishell

SRC_DIR=src
OBJ_DIR=obj
SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))


CC=cc
CFLAGS= -Wall -Wextra -Werror -g
LDFLAGS= -lreadline

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
INC=-I./include -I./$(LIBFT_DIR)/include


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN) Debut de la Compilation $(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(GREEN) Compilation Reussi $(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@echo $(RED) "Debut du nettoyage des objets "$(RESET)
	@rm -f $(OBJ)
	@echo "$(RED) Nettoyage des objets Reussi $(RESET)"
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED) Ouvre les fenetres $(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED) Ferme les fenetres $(RESET)"

re: fclean all
