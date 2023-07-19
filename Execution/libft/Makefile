NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

SRC = ft_isdigit.c ft_putnbr_fd.c ft_strmapi.c ft_isprint.c ft_putstr_fd.c ft_strncmp.c ft_strcmp.c\
ft_itoa.c ft_split.c ft_strnstr.c ft_atoi.c ft_memchr.c ft_strchr.c ft_strrchr.c ft_bzero.c ft_memcmp.c\
ft_strdup.c ft_strtrim.c ft_calloc.c ft_memcpy.c ft_striteri.c ft_substr.c ft_isalnum.c ft_memmove.c\
ft_strjoin.c ft_tolower.c ft_isalpha.c ft_memset.c ft_strpchr.c ft_strlcat.c ft_toupper.c ft_putchar_fd.c\
ft_strlcpy.c ft_isascii.c ft_putendl_fd.c ft_strlen.c get_next_line.c\


SRCB = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)


bonus : $(OBJB)
	ar -rc $(NAME) $(OBJB)

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean all
