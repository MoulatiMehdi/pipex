CC = cc 
CCFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRCS_M = cmd.c env.c error.c main.c path.c process.c
SRCS_B = cmd_bonus.c  env_bonus.c  error_bonus.c  here_doc_bonus.c  main_bonus.c  path_bonus.c  process_bonus.c

OBJS_M = $(SRCS_M:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

NAME = pipex
LIBFT = libft/libft.a

all : $(NAME) 

bonus : $(OBJS_B) $(LIBFT) pipex_bonus.h 
	$(CC) $(CCFLAGS) $(OBJS_B) -lft -Llibft -o $(NAME)	

$(NAME) :  $(LIBFT) $(OBJS_M) pipex.h
	$(CC) $(CCFLAGS) $(OBJS_M) -lft -Llibft -o $@	

$(LIBFT) : 
	make -C libft --no-print-directory

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean : 
	make clean -C libft --no-print-directory
	rm -rf $(OBJS_B) $(OBJS_M)
fclean : clean
	make fclean -C libft --no-print-directory
	rm -rf $(NAME)

re : fclean all 

.PHONY : re clean fclean all bonus 
.SECONDARY: $(OBJS_B) $(OBJS_M)
