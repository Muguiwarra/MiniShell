# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabboune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 23:13:53 by nabboune          #+#    #+#              #
#    Updated: 2023/07/19 18:45:33 by nabboune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

CC = cc

MSG = "auto_commit"

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

NEEDED_FLAGS = -lreadline

SRCS =	Minishell.c \
		src/ft_dprintf/ft_dputchar.c \
		src/ft_dprintf/dstrformat.c \
		src/ft_dprintf/ft_dputptr.c \
		src/ft_dprintf/ft_dprintf.c \
		src/ft_dprintf/ft_dputhex.c \
		src/ft_dprintf/ft_dputstr.c \
		src/ft_dprintf/ft_dputnbr.c \
		src/ft_malloc.c \
		Parsing/prompt.c \
		Parsing/files.c \
		Parsing/elem_op_dic.c \
		Parsing/dictionary.c \
		Parsing/parsing_out.c \
		Execution/cd.c \
		Execution/echo.c \
		Execution/env.c \
		Execution/env_utils.c \
		Execution/exit.c \
		Execution/export.c \
		Execution/export_print.c \
		Execution/pwd.c \
		Execution/unset.c

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

push :
	git add .
	git commit -m $(MSG)
	git push

.PHONY : all clean fclean re