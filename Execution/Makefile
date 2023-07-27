NAME = pipex
NAME_BONUS = pipex

CFLAGS = -Wall -Werror -Wextra

RLFLAGS = -lreadline

SRC =	pipex.c\
		add_char.c\
		get_cmd_path.c\
		err_msg.c\
		exec_cmd.c\
		here_doc.c\
		env.c\
		env_utils.c\
		env_to_arr.c\
		run_ps.c\
		t.c

# SRCB =	bonus/pipex_bonus.c\
# 		bonus/check_args_bonus.c\
# 		bonus/here_doc.c\
# 		bonus/run_ps_bonus.c\
# 		add_char.c\
# 		check_cmd_path.c\
# 		check_args.c\
# 		err_msg.c\
# 		exec_cmd.c

OBJ = $(SRC:.c=.o)

# OBJB = $(SRCB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	# make -C libft/
	$(CC) $(CFLAGS) $(RLFLAGS) -o $(NAME) $(OBJ) libft/libft.a


# bonus : $(OBJB)
# 	make -C libft/
# 	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJB) libft/libft.a

clean:
	# make clean -C libft/
	rm -f $(OBJ) $(OBJB)

fclean: clean
	# make fclean -C libft/
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all
