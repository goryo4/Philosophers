# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygorget <ygorget@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 14:44:21 by ygorget           #+#    #+#              #
#    Updated: 2025/02/19 13:42:13 by ygorget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
CC= cc
FLAGS= -Wall -Werror -Wextra
SRC=	action_utils.c		action.c	error.c\
		init_data.c			philo.c		monitoring.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re