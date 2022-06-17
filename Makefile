# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 11:09:19 by rmamison          #+#    #+#              #
#    Updated: 2022/06/17 16:25:31 by rmamison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
BONUS = pipex_bonus

SRC_UTILS =	utils_str.c utils_pipex.c 
DIR_SRC = srcs/utils/
PATH_UTILS = $(addprefix $(DIR_SRC), $(SRC_UTILS)) \
			get_next_line/get_next_line.c get_next_line/gnl_utils.c 
OB_UT = $(PATH_UTILS:.c=.o)

SRC_M = main.c
DIR_M = srcs/mandatory/
PATH_M = $(addprefix $(DIR_M), $(SRC_M))
OB_M = $(PATH_M:.c=.o)

SRC_B = main_bonus.c pipex_bonus.c here_doc.c
DIR_B = srcs/bonus/
PATH_B = $(addprefix $(DIR_B), $(SRC_B))
OB_B = $(PATH_B:.c=.o)

RM = rm -rf
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = -I./include -I./get_next_line/include/

CC = gcc

bold := $(shell tput bold)
col_yel = \033[33;33m

%.o : %.c 
	@echo -e "$(col_yel)=== $(bold)Creating the file object..."
	@$(CC) $(FLAGS) $(INCLUDE) -c $^ -o $@
	@echo -e "\033[0;35m $(bold)File object has been created $(col_yel):)"

$(NAME) : $(OB_UT) $(OB_M) 
	@echo -e "\033[0;36m$(bold) Compiling..."
	@$(CC) $(FLAGS) $^ -o $@
	@echo -e "$(col_yel)$(bold)[OK]. Compilation is done"

bonus : $(BONUS)
$(BONUS) : $(OB_UT) $(OB_B)
	@echo -e "\033[0;36m=== $(bold) Compiling bonus..."
	@$(CC) $(FLAGS) $^ -o $@
	@echo -e "$(col_yel)$(bold)[OK]. Compilation is done"


all : $(BONUS) $(NAME)

clean : 
	@$(RM) $(OB_UT)
	@$(RM) $(OB_M)
	@$(RM) $(OB_B)
	@$(RM) $(OB_GNL)
	@echo -e "\033[0;35m File object has been removed $(col_yel):)"

fclean : clean
	@$(RM) $(NAME) pipex_bonus
	@echo -e "\033[0;35m Binary file has been remoded $(col_yel):)"

re : fclean $(NAME)

.PHONY: all clean fclean re bonus
