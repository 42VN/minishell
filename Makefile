# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 16:57:00 by ktieu             #+#    #+#              #
#    Updated: 2024/11/19 10:15:52 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	cc
CFLAGS				=	-O3 -Wall -Wextra -Werror -I ./include
CFLAGS_DEV			=	-g -O3 -I ./include -fsanitize=address,undefined -g
CFLAGS_VALGRIND		=	-g -O3 -I ./include #-Wall -Wextra -Werror -I ./include

LIBFT_DIR			=	./libft
LIBFT_A				=	$(LIBFT_DIR)/libft.a
LINKER				=	-lreadline -L$(LIBFT_DIR) -lft

# **************************************************************************** #
#                     File and Directory Rules                                 #
# **************************************************************************** #

SRC_DIR				=	src
ENV_DIR				=	$(SRC_DIR)/env
SHELL_DIR			=	$(SRC_DIR)/shell
BUILTIN_DIR			=	$(SRC_DIR)/builtin
UTIL_DIR			=	$(SRC_DIR)/utility
AST_DIR				=	$(SRC_DIR)/ast
TOKEN_DIR			=	$(SRC_DIR)/token
EXEC_DIR			=	$(SRC_DIR)/execution
EXP_DIR				=	$(SRC_DIR)/expansion
SIG_DIR				=	$(SRC_DIR)/signals
OBJ_DIR				=	obj

SRC_BASE_FILES		=	main.c
ENV_FILES			=	env_sort.c env_dup.c env_get.c env_print.c env_set.c env_unset.c
SHELL_FILES			=	shell_init.c shell_cleanup.c
AST_FILES			=	build_ast.c	read_heredoc.c ast_utils.c
UTIL_FILES			=	ft_prompt.c ft_exit.c ft_error_ret.c ft_is_op.c ft_strjoin_space.c ft_split_cmd.c ft_split_cmd_utils.c
TOKEN_FILES			=	parse.c token.c free.c mem.c  utils.c operator.c cmd.c error.c print.c redirect.c
BUILTIN_FILES		=	env.c unset.c export.c cd_utils.c cd.c echo.c exit.c pwd.c export_utils.c
EXEC_FILES			= 	execute_ast.c execute_cmd.c error.c find_cmd_path.c utils.c
EXP_FILES			=	exp.c utils.c exp_dollar.c exp_tiddle.c exp_normal.c exp_single_quote.c
SIG_FILES			=	signals.c

SRC_FILES			=	$(addprefix $(SRC_DIR)/, $(SRC_BASE_FILES)) \
						$(addprefix $(ENV_DIR)/, $(ENV_FILES)) \
						$(addprefix $(SHELL_DIR)/, $(SHELL_FILES)) \
						$(addprefix $(UTIL_DIR)/, $(UTIL_FILES)) \
						$(addprefix $(AST_DIR)/, $(AST_FILES)) \
						$(addprefix $(TOKEN_DIR)/, $(TOKEN_FILES)) \
						$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES)) \
						$(addprefix $(EXEC_DIR)/, $(EXEC_FILES)) \
						$(addprefix $(EXP_DIR)/, $(EXP_FILES))\
						$(addprefix $(SIG_DIR)/, $(SIG_FILES))

OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
#                                  Build Rules                                 #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_A)
	$(CC) $(CFLAGS_VALGRIND) $(OBJ_FILES) $(LINKER) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS_VALGRIND) -c $< -o $@

$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT_DIR)

# **************************************************************************** #
#                                  Clean Rules                                 #
# **************************************************************************** #

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

# **************************************************************************** #
#                                  Phony Rules                                 #
# **************************************************************************** #
.PHONY: all clean fclean re