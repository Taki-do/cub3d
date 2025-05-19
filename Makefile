NAME        := cub3D

SRC_DIR     := srcs/
OBJ_DIR     := obj/
INCLUDE_DIR := includes/

PATH_LIBFT  := libft/
LIBFT_LIB   := $(PATH_LIBFT)libft.a

MLX_DIR     := minilibx-linux
MLX_LIB     := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_INCLUDE := -I$(MLX_DIR)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -I$(INCLUDE_DIR) $(MLX_INCLUDE)

SRC := \
	$(SRC_DIR)parsing/file_check.c \
	$(SRC_DIR)parsing/flood_fill.c \
	$(SRC_DIR)parsing/map_checking.c \
	$(SRC_DIR)parsing/parsing_elements.c \
	$(SRC_DIR)parsing/parsing.c \
	$(SRC_DIR)parsing/side_functions.c \
	$(SRC_DIR)raycasting/cub3d.c \
	$(SRC_DIR)raycasting/init.c \
	$(SRC_DIR)raycasting/input.c \
	$(SRC_DIR)raycasting/textures.c \
	$(SRC_DIR)raycasting/dda.c \
	$(SRC_DIR)rendering/render.c \
	$(SRC_DIR)rendering/window.c \
	$(SRC_DIR)rendering/minimap.c \
	$(SRC_DIR)utils/free.c \
	$(SRC_DIR)utils/utils.c \
	$(SRC_DIR)main.c \
	$(SRC_DIR)raycasting/monsters.c \
	$(SRC_DIR)raycasting/shotgun.c \
	$(SRC_DIR)raycasting/door.c

OBJ := $(SRC:$(SRC_DIR)%=$(OBJ_DIR)%)
OBJ := $(OBJ:.c=.o)


all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(PATH_LIBFT)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(PATH_LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(PATH_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
