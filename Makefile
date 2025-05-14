NAME = cub3D
PATH_LIBFT = libft/
LIBFT_LIB = $(PATH_LIBFT)libft.a
SRC_DIR = srcs/
OBJ_DIR = obj/
INCLUDE_DIR = includes/
SRC = $(SRC_DIR)parsing/file_check.c \
	$(SRC_DIR)parsing/flood_fill.c \
	$(SRC_DIR)parsing/map_checking.c \
	$(SRC_DIR)parsing/parsing_elements.c \
	$(SRC_DIR)parsing/parsing.c \
	$(SRC_DIR)utils/free.c \
	$(SRC_DIR)utils/utils.c \
	$(SRC_DIR)main.c
SRC_BONUS = 
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_LIB):
	make -C libft/

bonus: $(LIBFT_LIB) $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(LIBFT_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	/bin/rm -rf $(OBJ_DIR) $(OBJ_BONUS)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all