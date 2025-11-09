#### Variables ####
NAME =	philo
CC =	cc
FLAGS =	-Wall -Werror -Wextra -pthread -g3

SRC =	\
		actions.c \
		dinner_utils.c \
		getters_setters.c \
		init.c \
		parse.c \
		philo.c \
		time_utils.c \
		utils.c \

OBJ =	$(SRC:.c=.o)

#### Rules ####
# Declares rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
