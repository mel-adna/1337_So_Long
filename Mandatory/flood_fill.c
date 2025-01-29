/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:30:52 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/28 18:45:15 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	f_fill(char **tab, int row, int col, int *items)
{
	if (tab[row][col] == '1' || tab[row][col] == 'F')
		return ;
	if (tab[row][col] == 'C' || tab[row][col] == 'E')
		(*items)++;
	tab[row][col] = 'F';
	f_fill(tab, row + 1, col, items);
	f_fill(tab, row - 1, col, items);
	f_fill(tab, row, col + 1, items);
	f_fill(tab, row, col - 1, items);
}

static char	**copy_map(char **map)
{
	char	**map_copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	map_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!map_copy)
		error_exit("Memory allocation failed");
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			error_exit("Memory allocation failed");
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	map_check_path(char **map, int y, int x, int items)
{
	char	**map_copy;
	int		required_items;
	int		player_count;
	int		exit_count;
	int		collectible_count;

	map_copy = copy_map(map);
	count_components(map, &player_count, &exit_count, &collectible_count);
	required_items = exit_count + collectible_count;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'P')
			{
				f_fill(map_copy, y, x, &items);
				break ;
			}
			x++;
		}
		y++;
	}
	free_map(map_copy);
	return (items == required_items);
}
