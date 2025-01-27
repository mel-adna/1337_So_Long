#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "gnl/get_next_line_bonus.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <time.h>

typedef struct s_game
{
	void   *enemy;
	int		enemy_x;
	int		enemy_y;
    char    **map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*empty;
	int		tile_size;
	int		map_width;
	int		map_height;
	int		moves;
	int		player_x;
	int		player_y;
	int		collectibles;
}   t_game;


char    **read_map(const char *file_path);
void	validate_map(char **map, int i);
void    validate_components(char **map);
int		is_all_walls(const char *line);
void    error_exit(const char *message);
void    free_map(char **map);
void	render_map(t_game *game);
void	init_game(t_game *game, char *map_path);
void	load_textures(t_game *game);
void	handle_events(t_game *game);
void	init_player_position(t_game *game);
int		move_enemy(void *param);

#endif
