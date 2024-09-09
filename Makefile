# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 09:26:47 by hitran            #+#    #+#              #
#    Updated: 2024/09/05 11:44:21 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executables
NAME 			= minishell

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -lreadline
INCLUDES 		= -I./includes -I./$(MYLIB_DIR)/includes
RM 				= rm -f

# Directories
MAN_DIR 		= ./sources/mandatory
BONUS_DIR		= ./sources/bonus
MYLIB_DIR	 	= ./mylib

# Source files by directory
MAN_FILES 		=	minishell.c

BONUS_FILES 	=

MAN_SRCS		= 	main.c $(addprefix $(MAN_DIR)/, $(MAN_FILES))

BONUS_SRCS		=	main_bonus.c $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
					
# Library
MYLIB 			= $(MYLIB_DIR)/mylib.a

# Targets
all : mandatory

mandatory : .mandatory
.mandatory: $(MYLIB) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAN_SRCS) $(MYLIB) -o $(NAME)
	@touch .mandatory
	@$(RM) .bonus

bonus: .bonus
.bonus: $(MYLIB) $(BONUS_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_SRCS) $(MYLIB) -o $(NAME)
	@touch .bonus
	@$(RM) .mandatory

$(MYLIB):
	$(MAKE) -C $(MYLIB_DIR)

clean:
	$(MAKE) clean -C $(MYLIB_DIR)
	$(RM) .bonus .mandatory


fclean: clean
	$(MAKE) fclean -C $(MYLIB_DIR)
	$(RM) $(NAME) .bonus .mandatory
	
re: fclean all

.PHONY: all clean fclean re mandatory bonus