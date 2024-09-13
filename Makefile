# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 16:57:00 by ktieu             #+#    #+#              #
#    Updated: 2024/09/13 12:45:35 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	cc
CFLAGS				=	-O3 -Wall -Wextra -Werror -I ./include
CFLAGS_DEV			=	-g -O3 -I ./include

LIBFT_DIR			=	./libft
LIBFT_A				=	$(LIBFT_DIR)/libft.a
LINKER				=	-lreadline -L$(LIBFT_DIR) -lft

# **************************************************************************** #
#                     File and Directory Rules                                 #
# **************************************************************************** #

SRC_DIR				=	./src
ENV_DIR				=	$(SRC_DIR)/env
SHELL_DIR			=	$(SRC_DIR)/shell
UTIL_DIR			=	$(SRC_DIR)/utility
PARSE_DIR			=	$(SRC_DIR)/parse
BUILTIN_DIR			=	$(SRC_DIR)/builtin
OBJ_DIR				=	obj

SRC_BASE_FILES		=	main.c
ENV_FILES			=	envp_dup.c
SHELL_FILES			=	shell_init.c shell_cleanup.c
UTIL_FILES			=	ft_prompt.c ft_exit.c 	\
						locate_token.c
PARSE_FILES			=	parse.c	\
						build_ast.c

SRC_FILES			=	$(addprefix $(SRC_DIR)/, $(SRC_BASE_FILES)) \
						$(addprefix $(ENV_DIR)/, $(ENV_FILES)) \
						$(addprefix $(SHELL_DIR)/, $(SHELL_FILES)) \
						$(addprefix $(UTIL_DIR)/, $(UTIL_FILES))

OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
#                                  Build Rules                                 #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_A)
	$(CC) $(CFLAGS_DEV) $(OBJ_FILES) $(LINKER) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_DEV) -c $< -o $@

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

# **************************************************************************** #
#                                  Clean Rules                                 #
# **************************************************************************** #

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# **************************************************************************** #
#                                  Phony Rules                                 #
# **************************************************************************** #
.PHONY: all clean fclean re