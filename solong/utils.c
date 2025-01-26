/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:26:45 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/26 12:56:41 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *message)
{
	printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

void	free_map(char **map)
{
	int i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	validate_components(char **map)
{
	int i, j;
	int player_count = 0, exit_count = 0, collectible_count = 0;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				player_count++;
			else if (map[i][j] == 'E')
				exit_count++;
			else if (map[i][j] == 'C')
				collectible_count++;
			else if (map[i][j] != '1' && map[i][j] != '0')
				error_exit("Map contains invalid characters.");
			j++;
		}
		i++;
	}
	if (player_count != 1)
		error_exit("Map must have exactly one starting position (P).");
	if (exit_count != 1)
		error_exit("Map must have exactly one exit (E).");
	if (collectible_count < 1)
		error_exit("Map must have at least one collectible (C).");
}
