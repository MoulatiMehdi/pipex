CC = cc 
CCFLAGS = -Wall -Wextra -Werror


SRCS = $(wildcard *_bonus.c)
OBJS = $(SRCS:.c=.o)
NAME = pipex 
LIBFT = libft/libft.a

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CCFLAGS) $? -lft -Llibft -o $(NAME)	

$(LIBFT) : 
	make -C libft

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean : 
	make clean -C libft 
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : re fclean all 
