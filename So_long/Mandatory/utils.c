/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:20:55 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:41 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *message)
{
	ft_printf("\033[1;31mError\n%s\n\033[0m", message);
	exit(EXIT_FAILURE);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	count_components_helper(char c, int *player_count, int *exit_count,
		int *collectible_count)
{
	if (c == 'P')
		(*player_count)++;
	else if (c == 'E')
		(*exit_count)++;
	else if (c == 'C')
		(*collectible_count)++;
	else if (c != '1' && c != '0')
		error_exit("Map contains invalid characters.");
}

void	count_components(char **map, int *p_count, int *e_count, int *c_count)
{
	int	x;
	int	y;

	x = 0;
	*p_count = 0;
	*e_count = 0;
	*c_count = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			count_components_helper(map[x][y], p_count, e_count,
				c_count);
			y++;
		}
		x++;
	}
}

void	validate_components(char **map)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	count_components(map, &player_count, &exit_count, &collectible_count);
	if (player_count != 1)
		error_exit("Map must have exactly one starting position (P).");
	if (exit_count != 1)
		error_exit("Map must have exactly one exit (E).");
	if (collectible_count < 1)
		error_exit("Map must have at least one collectible (C).");
}
