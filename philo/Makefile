# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/29 17:07:11 by nsimon            #+#    #+#              #
#    Updated: 2021/08/03 00:45:56 by nsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC_PATH = ./includes/

SRC_PATH = ./src/

SRC_NAME =	main.c \
			utils.c \
			philo_action.c \
			monitor.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_PATH = ./objs/

OBJ_PATH_DEBUG = ./objs_DEBUG/

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

OBJ_DEBUG = $(addprefix $(OBJ_PATH_DEBUG), $(OBJ_NAME))

CC = clang $(CFLAGS)

CFLAGS = -pthread -Wall -Wextra -Werror

TEMP = .temp.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[34mCreation of $(NAME) ...\033[0m"
	@$(CC) $(OBJ) -o$(NAME)
	@echo "\033[32m$(NAME) created\n\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I$(INC_PATH) -o $@ -c $<

debug: $(OBJ_DEBUG)
	@echo "\033[34mCreation of $(NAME) ...\033[0m"
	@$(CC) $(OBJ_DEBUG) -fsanitize=thread -o$(NAME) -g
	@echo "\033[32m$(NAME) created\n\033[0m"

$(OBJ_PATH_DEBUG)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH_DEBUG) 2> /dev/null || true
	@$(CC) -DDEBUG=1 -fsanitize=thread -g -I$(INC_PATH) -o $@ -c $<

clean:
	@echo "\033[33mRemoval of .o files of $(NAME) ...\033[0m"
	@rm -f $(OBJ)
	@rm -f $(OBJ_DEBUG)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@rmdir $(OBJ_PATH_DEBUG) 2> /dev/null || true
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME) $(TEMP)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all

git:
	@git add .
	@git commit -m "$(NAME)"
	@git push

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h

.PHONY: all, clean, fclean, re
