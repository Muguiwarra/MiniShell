NAME = mini

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

CC = gcc

SRC = env_utils.c env.c export.c export_print.c main.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) libft/libft.a

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

