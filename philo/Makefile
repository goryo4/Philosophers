# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 14:44:21 by ygorget           #+#    #+#              #
#    Updated: 2025/02/21 15:32:20 by ygorget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
CC= cc
FLAGS= -Wall -Werror -Wextra
SRC=	action_utils.c		action.c	error.c\
		init_data.c			philo.c		monitoring.c\
		wait.c\

OBJ = $(SRC:.c=.o)

PREV_LINE	:=	\033[A

GREEN		:=	\033[1;32m
BLUE		:=	\033[1;34m
RED			:=	\033[1;31m
YELLOW		:=	\033[1;33m
RESET		:=	\033[0m

TOTAL_FILES	:=	$(words $(OBJ))
CURR_FILE	:=	0
BAR_LENGTH	:=	50
NAME_LENGTH	:=	50

define PROGRESS_BAR
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE) + 1))))
	@$(eval PERCENTAGE=$(shell echo $$(($(CURR_FILE) * 100 / $(TOTAL_FILES)))))
	@$(eval FILLED=$(shell echo $$(($(CURR_FILE) * $(BAR_LENGTH) / $(TOTAL_FILES)))))
	@printf "\rCompiling [%d/%d] %-$(NAME_LENGTH)s" $(CURR_FILE) $(TOTAL_FILES) "$(notdir $<)"
	@printf "\n"
	@printf "\r"
	@for i in `seq 1 $(FILLED)`; do printf "█"; done
	@for i in `seq 1 $$(($(BAR_LENGTH) - $(FILLED)))`; do printf "░"; done
	@printf " %3d%%" $(PERCENTAGE)
	@printf "$(PREV_LINE)\r"
	@sleep 0.01
endef

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\n${BLUE}Linking objects${RESET}\n"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "${GREEN}Binary $(NAME) successfully created${RESET}"

%.o: %.c
	$(PROGRESS_BAR)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re