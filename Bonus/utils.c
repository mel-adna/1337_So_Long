/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:20:55 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/29 12:41:12 by mel-adna         ###   ########.fr       */
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

void	count_components_helper(char c, int *p_c, int *e_c, int *c_c)
{
	if (c == 'P')
		(*p_c)++;
	else if (c == 'E')
		(*e_c)++;
	else if (c == 'C')
		(*c_c)++;
	else if (c != '1' && c != '0' && c != 'G')
		error_exit("Map contains invalid characters.");
}

void	count_components(char **map, int *p_c, int *e_c, int *c_c)
{
	int	x;
	int	y;

	x = 0;
	*p_c = 0;
	*e_c = 0;
	*c_c = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			count_components_helper(map[x][y], p_c, e_c, c_c);
			y++;
		}
		x++;
	}
}

void	validate_components(char **map)
{
	int	p_c;
	int	e_c;
	int	c_c;

	count_components(map, &p_c, &e_c, &c_c);
	if (p_c != 1)
		error_exit("Map must have exactly one starting position (P).");
	if (e_c != 1)
		error_exit("Map must have exactly one exit (E).");
	if (c_c < 1)
		error_exit("Map must have at least one collectible (C).");
}
