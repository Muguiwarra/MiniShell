
NAME = dprintf.a

CFLAGS = -Wall -Wextra -Werror

SRC = ft_dprintf.c ft_dputchar.c ft_dputptr.c ft_dputhex.c ft_dputnbr.c ft_dputstr.c dstrformat.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
