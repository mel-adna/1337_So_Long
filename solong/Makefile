NAME        = so_long
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
MLX_DIR     = mlx
LIBFT_DIR   = libft
MLX_LIB     = $(MLX_DIR)/libmlx.dylib
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(MLX_DIR) -I$(LIBFT_DIR)
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRC         = so_long.c gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c \
			utils.c map_parser.c \
			
OBJS        = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_LIB) -o $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) clean -C $(MLX_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
