/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:28:59 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/28 15:45:56 by mel-adna         ###   ########.fr       */
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
# include "mlx/mlx.h"

typedef struct s_game
{
	char	**map;
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
}	t_game;

char	**read_map(const char *file_path);
void	validate_map(char **map, int i);
void	validate_components(char **map);
int		is_all_walls(const char *line);
void	error_exit(const char *message);
void	free_map(char **map);
void	render_map(t_game *game);
void	init_game(t_game *game);
void	load_textures(t_game *game);
void	handle_events(t_game *game);
void	init_player_position(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
int		close_game(t_game *game);

#endif
