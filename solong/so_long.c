/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:26:52 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/26 13:01:32 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_all_walls(const char *line)
{
	while (*line)
	{
		if (*line != '1')
			return (0);
		line++;
	}
	return (1);
}

void	validate_map(char **map, int i)
{
	int	row_length;

	row_length = ft_strlen(map[0]);
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != row_length)
			error_exit("Map is not rectangular.");
		i++;
	}
	i = 0;
	while (map[i])
	{
		if ((i == 0 || map[i + 1] == NULL) && !is_all_walls(map[i]))
			error_exit("Top or bottom row is not surrounded by walls.");
		if (map[i][0] != '1' || map[i][row_length - 1] != '1')
			error_exit("Side walls are missing.");
		i++;
	}
	validate_components(map);
}

int	main(int argc, char	**argv)
{
	t_game	game;
	int		i;

	if (argc != 2)
		error_exit("Usage: ./so_long <map_file.ber>");
	game.map = read_map(argv[1]);
	validate_map(game.map, 0);
	i = 0;
	while (game.map[i])
		printf("%s\n", game.map[i++]);
	free_map(game.map);
	return (0);
}
