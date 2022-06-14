# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 11:09:19 by rmamison          #+#    #+#              #
#    Updated: 2022/06/14 16:41:45 by rmamison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRC_UTILS =	srcs/utils/utils_str.c \
	srcs/utils/utils_pipex.c \
	get_next_line/get_next_line.c \
	get_next_line/gnl_utils.c \

OB_UTILS = $(SRC_UTILS:%.c=%.o) 

SRC_M = srcs/mandatory/main.c
OB_M = $(SRC_M:%.c=%.o)

SRC_B = srcs/bonus/main_bonus.c \
		srcs/bonus/pipex_bonus.c \
		srcs/bonus/here_doc.c \

OB_B = $(SRC_B:%.c=%.o)

DIR_O = file_object
OB = $(OB_UTILS) $(OB_M) $(OB_B)

RM = rm -rf
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = -I./include -I./get_next_line/include/

CC = gcc

bold := $(shell tput bold)
col_yel = \033[0;33m

%.o : %.c
	@echo "$(COL)$(bold)Creating the file object..."
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[0;35m $(bold)File object has been created $(col_yel):)"

$(NAME) : $(OB_UTILS) $(OB_M) 
	@echo "\033[0;36m$(bold) Compiling..."
	@$(CC) $(FLAGS) $^ -o $@
	@mkdir -p $(DIR_O)
	@mv $(OB_UTILS) $(OB_M) $(DIR_O)
	@echo "$(col_yel)$(bold)[OK]. Compilation is done"

all : $(NAME)

bonus : $(OB_UTILS) $(OB_B)
	@echo "\033[0;36m$(bold) Compiling bonus..."
	@$(CC) $(FLAGS) $^ -o pipex_bonus
	@mkdir -p $(DIR_O)
	@mv $(OB_UTILS) $(OB_B) $(DIR_O)
	@echo "$(col_yel)$(bold)[OK]. Compilation is done"


clean : 
	@$(RM) $(DIR_O)
	@echo "\033[0;35m File object has been removed $(col_yel):)"

fclean : clean
	@$(RM) $(NAME) pipex_bonus
	@echo "\033[0;35m Binary file has been remoded $(col_yel):)"

re : fclean $(NAME)

.PHONY: all clean fclean re bonus
