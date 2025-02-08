CC = cc 
CCFLAGS = -Wall -Wextra -Werror

SRCS_M = cmd.c env.c error.c main.c path.c process.c
SRCS_B = cmd_bonus.c  env_bonus.c  error_bonus.c  here_doc_bonus.c  main_bonus.c  path_bonus.c  process_bonus.c

OBJS_M = $(SRCS_M:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

NAME = pipex 
LIBFT = libft/libft.a


all : $(NAME) 

bonus : $(OBJS_B)  
	$(CC) $(CCFLAGS) $? -lft -Llibft -o $(NAME)	

$(NAME) :  $(LIBFT) $(OBJS_M) 	
	$(CC) $(CCFLAGS) $(OBJS_M) -lft -Llibft -o $@	

$(LIBFT) : 
	make -C libft

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS_B) $(OBJS_M)
fclean : clean
	rm -rf $(NAME)

re : fclean all 

.PHONY : re clean fclean all bonus 
