# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 13:48:44 by rtavabil          #+#    #+#              #
#    Updated: 2024/03/12 15:09:03 by rtavabil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRC := philosophers.c arguments.c functions.c strings.c \
	   initialization.c algorithm.c utils.c 
OBJ := $(SRC:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror

OBJ_PATH := obj/
OBJS := $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJ_PATH) 

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean 

#philosophers.c arguments.c functions.c strings.c initialization.c algorithm.c utils.c 