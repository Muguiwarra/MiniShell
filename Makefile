# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabboune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 23:13:53 by nabboune          #+#    #+#              #
#    Updated: 2023/08/08 06:17:40 by nabboune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

CC = cc

MSG = "auto_commit"

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

NEEDED_FLAGS = -lreadline -L/goinfre/nabboune/homebrew/opt/readline/lib -I/goinfre/nabboune/homebrew/opt/readline/include

SRCS =	Minishell.c \
		src/ft_dprintf/ft_dputchar.c \
		src/ft_dprintf/dstrformat.c \
		src/ft_dprintf/ft_dputptr.c \
		src/ft_dprintf/ft_dprintf.c \
		src/ft_dprintf/ft_dputhex.c \
		src/ft_dprintf/ft_dputstr.c \
		src/ft_dprintf/ft_dputnbr.c \
		src/ft_malloc.c \
		Parsing/pre_prompt.c \
		Parsing/prompt.c \
		Parsing/expand.c \
		Parsing/elem_op_dic_00.c \
		Parsing/elem_op_dic_01.c \
		Parsing/pre_dic.c \
		Parsing/crea_dic.c \
		Parsing/check_dic.c \
		Parsing/heredoc.c \
		Parsing/dollar_core.c \
		Parsing/less_great_01.c \
		Parsing/less_great_00.c \
		Parsing/update_01_helpers.c \
		Parsing/update_02_helpers.c \
		Parsing/update_02_helpers_core.c \
		Parsing/get_limiter.c \
		Parsing/update_dic.c \
		Parsing/elem_op_dic_out.c \
		Parsing/dic_output.c \
		Parsing/fd_files.c \
		Execution/pipex.c\
		Execution/add_char.c\
		Execution/get_cmd_path.c\
		Execution/err_msg.c\
		Execution/exec_cmd.c\
		Execution/here_doc.c\
		Execution/env_to_arr.c\
		Execution/run_ps.c\
		Execution/t.c\
		Execution/utils.c \
		Execution/randomfn.c \
		Execution/builtins/env.c \
		Execution/builtins/env_utils.c \
		Execution/builtins/cd.c \
		Execution/builtins/echo.c \
		Execution/builtins/exit.c \
		Execution/builtins/export.c \
		Execution/builtins/export_print.c \
		Execution/builtins/pwd.c \
		Execution/builtins/unset.c \
		Execution/builtins/exec_builtins.c

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