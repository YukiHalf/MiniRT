NAME = miniRT

TEST_NAME = unit_tests

PARSER_TEST_NAME = parser_tests
PARSER_TEST_SRC = test/parser_main.c


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
	src/scene/ray_features.c \
	src/scene/intersection_features.c \
	src/scene/intersection_features_2.c \
	src/scene/objects_features.c \
	src/matrix/matrix_features.c \
	src/matrix/matrix_features_2.c \
	src/matrix/matrix_features_3.c \
	src/matrix/matrix_features_4.c \
	src/matrix/matrix_features_5.c \
	src/matrix/matrix_features_6.c \
	src/mlx/mlx_features.c \
	src/math/double_features.c \
	src/app.c \
	src/error.c \
	src/hooks.c \
	src/pixel.c \
	src/render.c \
	src/shade.c \
	src/scene_parser/file_reader.c \
	src/scene_parser/number_util.c \
	src/scene_parser/parse_objects.c \
	src/scene_parser/parse_room.c \
	src/scene_parser/parse_util.c \
	src/scene_parser/parse_vec.c \
	src/scene_parser/scene_checker.c \
	src/scene_parser/scene_parser.c \
	src/scene_parser/scene_parser2.c
MAIN = src/main.c

TEST_SRC = test/test_main.c


OBJS = $(SRCS:.c=.o)
MAIN_OBJS = $(MAIN:.c=.o)
TEST_OBJS = $(TEST_SRC:.c=.o)
PARSER_TEST_OBJS = $(PARSER_TEST_SRC:.c=.o)
DEPS = $(OBJS:.o=.d) $(MAIN_OBJS:.o=.d) $(TEST_OBJS:.o=.d) $(PARSER_TEST_OBJS:.o=.d)

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

ptest: $(OBJS) $(PARSER_TEST_OBJS) $(LIBFT) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(PARSER_TEST_OBJS) $(OBJS) $(LIBS) -o $(PARSER_TEST_NAME)
	./$(PARSER_TEST_NAME)

$(OBJS) $(MAIN_OBJS) $(TEST_OBJS) $(PARSER_TEST_OBJS): | $(MLX42_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(INC_LIB) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN_OBJS) $(TEST_OBJS) $(PARSER_TEST_OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(TEST_NAME) $(PARSER_TEST_NAME)
	$(RM) $(MLX42_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re test ptest

-include $(DEPS)


