/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:55:55 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/30 12:16:54 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i < 5 || path[i - 1] != 'r' || path[i - 2] != 'e' || path[i - 3] != 'b'
		|| path[i - 4] != '.' || path[i - 5] == '/')
		error_exit("Invalid map file extension.");
}

char	*read_and_concat_file(int fd)
{
	char	*line;
	char	*temp_map;
	char	*temp;

	temp_map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!temp_map)
			temp_map = ft_strdup(line);
		else
		{
			temp = temp_map;
			temp_map = ft_strjoin(temp_map, line);
			free(temp);
		}
		if (line[0] == '\n' || line[0] == '\0')
			error_exit("Map is not rectangular.");
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (temp_map);
}

char	**read_map(const char *file_path)
{
	int		fd;
	char	*temp_map;
	char	**map;

	check_path((char *)file_path);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open the map file.");
	temp_map = read_and_concat_file(fd);
	close(fd);
	if (!temp_map)
		error_exit("Map is empty.");
	map = ft_split(temp_map, '\n');
	free(temp_map);
	return (map);
}

void	put_tile_to_window(t_game *g, int x, int y, void *tile)
{
	mlx_put_image_to_window(g->mlx, g->win, tile,
		x * g->tile_size, y * g->tile_size);
}

void	render_map(t_game *g, int x, int y)
{
	mlx_clear_window(g->mlx, g->win);
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			if (g->map[y][x] == '1')
				put_tile_to_window(g, x, y, g->wall);
			else if (g->map[y][x] == '0')
				put_tile_to_window(g, x, y, g->empty);
			else if (g->map[y][x] == 'P')
				put_tile_to_window(g, x, y, g->player);
			else if (g->map[y][x] == 'C')
				put_tile_to_window(g, x, y, g->collectible);
			else if (g->map[y][x] == 'E')
				put_tile_to_window(g, x, y, g->exit);
			else if (g->map[y][x] == 'G')
				put_tile_to_window(g, x, y, g->ghost_frames[g->current_frame]);
			x++;
		}
		y++;
	}
}
