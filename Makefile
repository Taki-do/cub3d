NAME = cub3D
LIBFT_LIB = libft/libft.a
INC_DIR = includes
SRCS = srcs/raycasting/main.c srcs/raycasting/minilibx.c srcs/raycasting/pixel_display.c \
		srcs/parsing/file_check.c srcs/parsing/flood_fill.c srcs/parsing/map_checking.c \
		srcs/parsing/parsing_elements.c srcs/parsing/parsing.c srcs/utils/free.c \
		srcs/utils/utils.c srcs/main.c
SRC_BONUS = 
OBJS = $(SRCS:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
CC = gcc
FLAGS =  -I$(INC_DIR) -Wall -Wextra -Werror
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	make -C libft/

bonus: $(LIBFT_LIB) $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(LIBFT_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf srcs/*/*.o
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
