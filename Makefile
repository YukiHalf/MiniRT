NAME = miniRT

TEST_NAME = unit_tests


CC = cc
UNAME_S := $(shell uname -s)
MLX42_DIR = MLX42
CFLAGS := -Wall -Wextra -g -IIncludes -O3 -Ofast -ffast-math -flto -march=native -Ilibft -I$(MLX42_DIR)/include/MLX42 -MMD -MP
INCLUDES = -Iinc
RM = rm -Rf
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
ifeq ($(UNAME_S),Linux)
	LIBS = $(LIBFT) $(MLX42_LIB) -ldl -pthread -lm -lglfw -lGL -lX11 -Iinclude
else
	GLFW_PREFIX := $(shell brew --prefix glfw)
	LIBS = $(LIBFT) $(MLX42_LIB) -L$(GLFW_PREFIX)/lib -ldl -pthread -lm -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

SRCS = src/tuple/tuple_features.c \
	src/tuple/tuple_features_2.c \
	src/tuple/tuple_features_3.c \
	src/color/color_feature.c \
	src/scene/scene_features.c \
	src/matrix/matrix_features.c \
	src/matrix/matrix_features_2.c \
	src/matrix/matrix_features_3.c \
	src/mlx/mlx_features.c \
	src/math/double_features.c
MAIN = src/main.c

TEST_SRC = test/test_main.c


OBJS = $(SRCS:.c=.o)
MAIN_OBJS = $(MAIN:.c=.o)
TEST_OBJS = $(TEST_SRC:.c=.o)
DEPS = $(OBJS:.o=.d) $(MAIN_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

INC_LIB = -I$(LIBFT_DIR)/
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = inc/libft


all: $(NAME)

$(NAME): $(OBJS) $(MAIN_OBJS) $(LIBFT) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(MLX42_LIB):
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@if [ ! -f "$(MLX42_LIB)" ]; then \
		echo "$(COLOR_GREEN)Building MLX42...$(COLOR_RESET)"; \
		cmake $(MLX42_DIR) -B $(MLX42_DIR)/build; \
		make -C $(MLX42_DIR)/build -j4; \
	fi
	@echo "$(COLOR_GREEN)MLX42 ready$(COLOR_RESET)"

test: $(OBJS) $(TEST_OBJS) $(LIBFT) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS)  $(LIBS) -o $(TEST_NAME)
	./$(TEST_NAME)

$(OBJS) $(MAIN_OBJS) $(TEST_OBJS): | $(MLX42_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(INC_LIB) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN_OBJS) $(TEST_OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)
	$(RM) $(MLX42_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re

-include $(DEPS)


