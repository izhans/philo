#### Variables ####
NAME =	philo
CC =	cc
FLAGS =	-Wall -Werror -Wextra

SRC =	philo.c \
		parse.c \
		utils.c \

OBJ =	$(SRC:.c=.o)

#### Rules ####
# Declares rules
.PHONY: all clean fclean re debug

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

debug: FLAGS += -g3
debug: all
