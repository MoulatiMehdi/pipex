CC = cc 
CCFLAGS = -Wall -Wextra -Werror

SRCS_M = cmd.c env.c error.c main.c path.c process.c
SRCS_B = cmd_bonus.c  env_bonus.c  error_bonus.c  here_doc_bonus.c  main_bonus.c  path_bonus.c  process_bonus.c

OBJS_M = $(SRCS_M:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

NAME = pipex 
LIBFT = libft/libft.a

.PHONY : re clean fclean all bonus 
.FEATURES = 'target-specific'

all : $(NAME) 

bonus : $(NAME)  


$(NAME) :  $(LIBFT) $(OBJS_M) 	
	$(CC) $(CCFLAGS) $(OBJS) -lft -Llibft -o $@	

$(LIBFT) : 
	make -C libft

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)

re : fclean all

