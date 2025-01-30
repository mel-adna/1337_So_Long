/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:43:24 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/30 12:15:57 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_ghost_status(t_game *game, int new_x, int new_y)
{
	if (game->gost_x == game->player_x && game->gost_y == game->player_y)
	{
		ft_printf("\033[1;31m\nGame Over! The ghost caught you!\n\033[0m");
		ft_printf("\033[1;33m\n         Score: %d moves\n\n\033[0m", game->moves);
		close_game(game);
		return (0);
	}
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == '1'
		|| game->map[new_y][new_x] == 'E'
		|| game->map[new_y][new_x] == 'C')
		return (0);
	return (1);
}

static void	update_ghost_pos(t_game *game, int new_x, int new_y)
{
	game->map[game->gost_y][game->gost_x] = '0';
	game->gost_x = new_x;
	game->gost_y = new_y;
	game->map[new_y][new_x] = 'G';
	render_map(game, 0, 0);
	game_draw_collectibles(game);
}

static void	chase_mode(t_game *game, int *x, int *y)
{
	int	dx;
	int	dy;

	dx = abs(game->player_x - game->gost_x);
	dy = abs(game->player_y - game->gost_y);
	if (dx > dy)
	{
		if (game->player_x > game->gost_x)
			(*x)++;
		else
			(*x)--;
	}
	else
	{
		if (game->player_y > game->gost_y)
			(*y)++;
		else
			(*y)--;
	}
}

static void	set_ghost_move(t_game *g, int *new_x, int *new_y)
{
	int	direction;

	*new_x = g->gost_x;
	*new_y = g->gost_y;
	if (abs(g->player_x - g->gost_x) + abs(g->player_y - g->gost_y) < 5)
		chase_mode(g, new_x, new_y);
	else
	{
		direction = rand() % 5;
		if (direction == 0)
			(*new_x)++;
		else if (direction == 1)
			(*new_x)--;
		else if (direction == 2)
			(*new_y)++;
		else
			(*new_y)--;
	}
}

int	move_gost(void *param)
{
	t_game		*game;
	int			new_x;
	int			new_y;
	static int	delay = 0;

	game = (t_game *)param;
	if (check_ghost_status(game, game->gost_x, game->gost_y) == 0)
		return (0);
	animate_ghost(game);
	if (++delay < 4000)
		return (1);
	delay = 0;
	set_ghost_move(game, &new_x, &new_y);
	if (check_ghost_status(game, new_x, new_y))
		update_ghost_pos(game, new_x, new_y);
	return (1);
}
