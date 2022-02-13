NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

C_PATH = srcs/

O_PATH = objs/

H_PATH = includes/

SRCS_F = main.c \
		 sh_array.c \
		 sh_cd.c \
		 sh_env.c \
		 sh_help_echo_exit.c \
		 sh_process.c \
		 sh_stat.c

OBJS_F = $(SRCS_F:.c=.o)

SRCS = $(addprefix $(C_PATH), $(SRCS_F))
OBJS = $(addprefix $(O_PATH), $(OBJS_F))

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(FLAGS) $(OBJS) -L libft -lft -o $(NAME)

$(O_PATH)%.o: $(C_PATH)%.c
	mkdir -p objs
	$(CC) $(FLAGS) -I $(H_PATH) -I libft/includes -o $@ -c $<

clean :
	make -C libft clean
	rm -rf $(OBJS)
	rm -rf $(O_PATH)

fclean : clean
	make -C libft fclean
	rm -rf $(NAME)

re : fclean all
