# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaammo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 15:43:13 by souaammo          #+#    #+#              #
#    Updated: 2025/04/03 15:43:15 by souaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Philo_main.c  Philo_parsing.c  Philo_routine.c Philo_monitor.c malloc/malloc.c malloc/malloc_utils.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

RM = rm -rf

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
