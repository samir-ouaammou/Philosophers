SRC = Philo_mian.c  Philo_parsing.c  Philo_routine.c malloc/malloc.c malloc/malloc_utils.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

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
