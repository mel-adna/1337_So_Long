/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:27 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/29 09:36:17 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_collectibles(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				game->collectibles++;
			x++;
		}
		y++;
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Failed to initialize MiniLibX.");
	game->tile_size = 32;
	game->map_height = 0;
	while (game->map[game->map_height])
		game->map_height++;
	game->map_width = ft_strlen(game->map[0]);
	game->collectibles = 0;
	game->moves = 0;
	count_collectibles(game);
	init_player_position(game);
	game->win = mlx_new_window(game->mlx, game->map_width * game->tile_size,
			game->map_height * game->tile_size, "So Long");
	if (!game->win)
		error_exit("Failed to create a game window.");
	load_textures(game);
	render_map(game);
	handle_events(game);
	mlx_loop(game->mlx);
}

void	init_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit("Player position not found in map.");
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 53)
		close_game(game);
	else if (keycode == 123)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == 124)
		move_player(game, game->player_x + 1, game->player_y);
	else if (keycode == 126)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == 125)
		move_player(game, game->player_x, game->player_y + 1);
	return (0);
}

void	handle_events(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 17, 0L, close_game, game);
}
