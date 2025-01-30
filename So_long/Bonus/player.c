/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:16:48 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/30 15:56:27 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
}

int	handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E')
	{
		if (game->collectibles > 0)
			return (0);
		ft_printf("\033[1;32m\nCongratulations! You won!\n\033[0m");
		ft_printf("\033[1;33m\n    Score: %d moves\n\n\033[0m", game->moves + 1);
		close_game(game);
	}
	return (1);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width || 
		new_y < 0 || new_y >= game->map_height)
		return ;
	if (game->map[new_y][new_x] == '1')
		return ;
	handle_collectible(game, new_x, new_y);
	if (!handle_exit(game, new_x, new_y))
		return ;
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	game->moves++;
	ft_printf("\033[1;32mMoves: \033[0m\033[1;34m%d\033[0m\n", game->moves);
	render_map(game, 0, 0);
	game_draw_collectibles(game);
}

void	load_textures(t_game *g)
{
	int	size;

	size = g->tile_size;
	g->wall = mlx_xpm_file_to_image(g->mlx, "textures/wall.xpm", &size, &size);
	g->player = mlx_xpm_file_to_image(g->mlx, "textures/player.xpm", &size,
			&size);
	g->collectible = mlx_xpm_file_to_image(g->mlx, "textures/collectible.xpm",
			&size, &size);
	g->exit = mlx_xpm_file_to_image(g->mlx, "textures/exit.xpm", &size, &size);
	g->empty = mlx_xpm_file_to_image(g->mlx, "textures/empty.xpm", &size,
			&size);
	g->ghost_frames[0] = mlx_xpm_file_to_image(g->mlx, 
			"textures/B/ghost_down.xpm", &size, &size);
	g->ghost_frames[1] = mlx_xpm_file_to_image(g->mlx, 
			"textures/B/ghost_left.xpm", &size, &size);
	g->ghost_frames[2] = mlx_xpm_file_to_image(g->mlx, 
			"textures/B/ghost_down.xpm", &size, &size);
	g->ghost_frames[3] = mlx_xpm_file_to_image(g->mlx, 
			"textures/B/ghost_right.xpm", &size, &size);
	if (!g->wall || !g->player || !g->collectible || !g->exit || !g->empty)
		error_exit("Failed to load textures.");
	if (!g->ghost_frames[0] || !g->ghost_frames[1] || !g->ghost_frames[2] || 
		!g->ghost_frames[3])
		error_exit("Failed to load gost textures.");
}

int	close_game(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->collectible)
		mlx_destroy_image(game->mlx, game->collectible);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->ghost_frames[game->current_frame])
		mlx_destroy_image(game->mlx, game->ghost_frames[game->current_frame]);
	if (game->map)
		free_map(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
}
