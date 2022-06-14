# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 11:09:19 by rmamison          #+#    #+#              #
#    Updated: 2022/06/03 17:06:42 by rmamison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRC =	srcs/utils.c \
	srcs/utils_pipex.c \
	get_next_line/get_next_line.c \
	get_next_line/gnl_utils.c \
OB_SRC = $(SRC:%.c=%.o) 

SRC_M = srcs/mandatory/main.c srcs/mandatory/pipex.c
OB_M = $(SRC_M:%.c=%.o)

SRC_B = srcs/bonus/main_bonus.c srcs/bonus/pipex_bonus.c \
	srcs/bonus/here_doc.c \
OB_B = $(SRC_B:%.c=%.o)

DIR_O = file_object
OB = $(OB_SRC) $(OB_M) $(OB_B)

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

$(NAME) : $(OB)
	@echo "\033[0;36m$(bold) Compiling..."
	@$(CC) $(FLAGS) $(OB) $(INCLUDE) -o $@
	@mkdir -p $(DIR_O)
	@mv $(OB) $(DIR_O)
	@echo "$(col_yel)$(bold)[OK]. Compilation is done"

all : $(NAME)

clean : 
	@$(RM) $(DIR_O)
	@echo "\033[0;35m File object has been removed $(col_yel):)"

fclean : clean
	@$(RM) $(NAME)
	@echo "\033[0;35m Binary file has been remoded $(col_yel):)"

re : fclean $(NAME)

COL = \033[0;33m

.PHONY: all clean fclean re
