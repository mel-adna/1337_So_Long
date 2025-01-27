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

void	count_components(char **map, int *player_count, int *exit_count, int *collectible_count, int *enemy_count)
{
	int	x;
	int	y;

	x = 0;
	*player_count = 0;
	*exit_count = 0;
	*collectible_count = 0;
	*enemy_count = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
				(*player_count)++;
			else if (map[x][y] == 'E')
				(*exit_count)++;
			else if (map[x][y] == 'C')
				(*collectible_count)++;
			else if (map[x][y] == 'X')
				(*enemy_count)++;
			else if (map[x][y] != '1' && map[x][y] != '0')
				error_exit("Map contains invalid characters.");
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
	int	enemy_count;

	count_components(map, &player_count, &exit_count, &collectible_count, &enemy_count);
	if (player_count != 1)
		error_exit("Map must have exactly one starting position (P).");
	if (exit_count != 1)
		error_exit("Map must have exactly one exit (E).");
	if (collectible_count < 1)
		error_exit("Map must have at least one collectible (C).");
}

void render_map(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);

    for (int y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall, x * game->tile_size, y * game->tile_size);
            else if (game->map[y][x] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->empty, x * game->tile_size, y * game->tile_size);
            else if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->player, x * game->tile_size, y * game->tile_size);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible, x * game->tile_size, y * game->tile_size);
            else if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit, x * game->tile_size, y * game->tile_size);
			else if (game->map[y][x] == 'X')
				mlx_put_image_to_window(game->mlx, game->win, game->enemy, x * game->tile_size, y * game->tile_size);
        }
    }
}


