/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:28:59 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/30 17:00:56 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "gnl/get_next_line_bonus.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "../mlx/mlx.h"

typedef struct s_game
{
	char	**map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*player;
	void	*collectible;
	void	*original_map;
	void	*exit;
	void	*empty;
	void	*ghost_frames[5];
	int		current_frame;
	int		gost_x;
	int		gost_y;
	int		tile_size;
	int		map_width;
	int		map_height;
	int		moves;
	int		player_x;
	int		player_y;
	int		collectibles;
	char	prev_tile;
}	t_game;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

int		map_check_path(char **map, int y, int x, int items);
char	**read_map(const char *file_path);
void	validate_map(char **map, int i);
void	validate_components(char **map);
int		is_all_walls(const char *line);
void	error_exit(const char *message);
void	free_map(char **map);
void	render_map(t_game *game, int x, int y);
void	init_game(t_game *game);
void	load_textures(t_game *game);
void	handle_events(t_game *game);
void	init_player_position(t_game *game);
void	init_gost_position(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
int		close_game(t_game *game);
void	count_components(char **map, int *p_c, int *e_c, int *c_c);
int		move_gost(void *param);
int		animate_ghost(void *param);
void	game_draw_collectibles(t_game *game);
void	count_collectibles(t_game *game);

#endif