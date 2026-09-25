NAME = UnitTests

CC = cc
CFLAGS = -Wextra -Wall 
RM = rm -Rf

SRCS = tuple_test.c test_main.c 
OBJS = $(SRCS:.c=.o)


INC = -Ilibft/
LIBS = -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ../libft


all: $(NAME)
	


$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 

fclean: clean 
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean 

re: fclean 
	$(MAKE) all 

.PHONY: all clean fclean re 


