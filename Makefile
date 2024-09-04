NAME					=		minishell

CFLAGS					=		-O3 -Wall -Wextra -Werror  -I ./includes
CFLAGS_DEV				=		-g -O3 -lreadline -I ./includes

LINKER					= 		-lreadline

CC						=		cc

SRC_DIR					=		./src/
SRC_FILES				=		$(SRC_DIR)/main.c

OBJ_DIR					=		obj
OBJ_FILES				=		$(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS_DEV) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS_DEV) $(OBJ_FILES)  ${LINKER} -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re