CC = cc 
CCFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard *.c)
NAME = pipex 
LIBFT = libft/libft.a

all : $(NAME)


$(NAME) : $(LIBFT) $(SRCS)
	$(CC) $(CCFLAGS) $(SRCS) -lft -Llibft -o $(NAME)	

$(LIBFT) : 
	make -C libft

clean : 
	make clean -C libft 

fclean : clean

re : fclean all


.PHONY : re fclean all 
