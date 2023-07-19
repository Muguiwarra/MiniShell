# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabboune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 23:13:53 by nabboune          #+#    #+#              #
#    Updated: 2023/07/19 09:04:38 by nabboune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

NEEDED_FLAGS = -lreadline

SRCS =	Minishell.c \
		Parsing/prompt.c \
		Parsing/files.c \
		Parsing/elem_op_dic.c \
		Parsing/dictionary.c \
		Parsing/parsing_out.c \
		#Parsing/testing.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(NEEDED_FLAGS) -o $(NAME) $(LIBFT) $(OBJS)

$(LIBFT) :
	cd Libft/ && $(MAKE) && mv $(LIBFT) ..

all : $(NAME)

clean :
	cd Libft && $(MAKE) clean && cd .. && $(RM) $(OBJS) libft.a

fclean : clean
	cd Libft && $(MAKE) fclean && cd .. && $(RM) $(LIBFT) $(NAME)

re : fclean all

.PHONY : all clean fclean re