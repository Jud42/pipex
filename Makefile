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

SRCS = $(addsuffix .c, main pipex str_utils ft_split utils_pipex)

DIR_S = srcs
DIR_O = file_object

RM = rm -rf
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = -I include
CC = clang

bold := $(shell tput bold)
col_yel = \033[0;33m

SR = $(addprefix $(DIR_S)/, $(SRCS))
OB = $(addprefix $(DIR_O)/, $(SRCS:%.c=%.o))

$(DIR_O)/%.o : $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	@echo "\033[0;36m$(bold)Creating the file object..."
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[0;35m $(bold)File object has been created $(col_yel):)"

$(NAME) : $(OB)
	@echo "\033[0;36m$(bold) Compiling..."
	$(CC) $(FLAGS) $(OB) -o $@
	@echo "$(col_yel)$(bold)[OK]. Compilation is done"

all : $(NAME)

clean : 
	@$(RM) $(DIR_O)
	@echo "\033[0;35m File object has been removed $(col_yel):)"

fclean : clean
	@$(RM) $(NAME)
	@echo "\033[0;35m Binary file has been remoded $(col_yel):)"

re : fclean $(NAME)

.PHONY: all clean fclean re
