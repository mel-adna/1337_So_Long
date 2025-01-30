NAME        = so_long_bonus
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
MLX_DIR     = ../mlx
LIBFT_DIR   = libft
FT_PRINTF_DIR = ft_printf
MLX_LIB     = $(MLX_DIR)/libmlx.dylib
FT_PRINTF  = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRC         = so_long.c gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c \
			utils.c map_parser.c utils1.c player.c flood_fill.c gost.c \
			
OBJS        = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(FT_PRINTF) $(NAME) clean $(export DYLD_LIBRARY_PATH=$(pwd)/../mlx:$DYLD_LIBRARY_PATH)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(FT_PRINTF) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_LIB) $(FT_PRINTF) -o $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) clean -C $(MLX_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
