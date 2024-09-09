# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 09:26:47 by hitran            #+#    #+#              #
#    Updated: 2024/09/09 15:33:52 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executables
NAME 			=	minishell

# Compiler and flags
CC 				=	cc
CFLAGS 			=	-Wall -Wextra -Werror -lreadline
INCLUDES 		=	-I./includes -I./$(MYLIB_DIR)/includes
RM 				=	rm -f

# Directories
SRCS_DIR		=	./sources
PARSE_DIR 		=	$(SRCS_DIR)/parse
SIGNAL_DIR 		=	$(SRCS_DIR)/signal
EXECUTION_DIR 	=	$(SRCS_DIR)/execution
BUILTIN_DIR 	=	$(SRCS_DIR)/builtin
UTILS_DIR 		=	$(SRCS_DIR)/utils
MYLIB_DIR	 	=	./mylib

# Source files by directory
PARSE_FILES 	=	parse_input.c

SIGNAL_FILES 	=	wait_signal.c
EXECUTION_FILES =	
BUILTIN_FILES 	=	
UTILS_FILES 	=	error.c
# get_envp.c \
					

MAN_SRCS		=	main.c 													\
					$(addprefix $(PARSE_DIR)/, $(PARSE_FILES)) 				\
					$(addprefix $(SIGNAL_DIR)/, $(SIGNAL_FILES))			\
					$(addprefix $(EXECUTION_DIR)/, $(EXECUTION_FILES)) 		\
					$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES)) 			\
					$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

BONUS_SRCS		=	main_bonus.c 											\
					$(addprefix $(PARSE_DIR)/, $(PARSE_FILES)) 				\
					$(addprefix $(SIGNAL_DIR)/, $(SIGNAL_FILES))			\
					$(addprefix $(EXECUTION_DIR)/, $(EXECUTION_FILES)) 		\
					$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES)) 			\
					$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
					
# Library
MYLIB 			=	$(MYLIB_DIR)/mylib.a

# Targets
all : mandatory

mandatory 		:	.mandatory
.mandatory		:	$(MYLIB) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAN_SRCS) $(MYLIB) -o $(NAME)
	@touch .mandatory
	@$(RM) .bonus

bonus			:	.bonus
.bonus			:	$(MYLIB) $(BONUS_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_SRCS) $(MYLIB) -o $(NAME)
	@touch .bonus
	@$(RM) .mandatory

$(MYLIB):
	$(MAKE) -C $(MYLIB_DIR)

clean:
	$(MAKE) clean -C $(MYLIB_DIR)
	$(RM) .bonus .mandatory


fclean			:	clean
	$(MAKE) fclean -C $(MYLIB_DIR)
	$(RM) $(NAME) .bonus .mandatory
	
re: fclean all

.PHONY: all clean fclean re mandatory bonus