NAME = miniRT

TEST_NAME = unit_tests


CC = cc
CFLAGS = -Wextra -Wall
INCLUDES = -Iinc
RM = rm -Rf

SRCS = src/tuple/tuple_features.c \
	src/tuple/tuple_features_2.c \
	src/tuple/tuple_features_3.c

MAIN = src/main.c

TEST_SRC = test/test_main.c


OBJS = $(SRCS:.c=.o)
MAIN_OBJS = $(MAIN:.c=.o)
TEST_OBJS = $(TEST_SRC:.c=.o)

INC_LIB = -I$(LIBFT_DIR)/
LIBS = -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = inc/libft


all: $(NAME)

$(NAME): $(OBJS) $(MAIN_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

test: $(OBJS) $(TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) $(LIBS) -o $(TEST_NAME)
	./$(TEST_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(INC_LIB) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN_OBJS) $(TEST_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re


