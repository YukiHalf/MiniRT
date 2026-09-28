NAME = UnitTests

CC = cc
CFLAGS = -Wextra -Wall
RM = rm -Rf

SRCS = array_test.c test_main.c tuple_features_2.c tuple_features.c \
		float_features.c tuple_features_3.c
OBJS = $(SRCS:.c=.o)


INC = -Ilibft/
LIBS = -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ../inc/libft


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


