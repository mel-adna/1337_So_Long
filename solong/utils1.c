#include "so_long.h"

void init_game(t_game *game, char *map_path)
{
    game->map = read_map(map_path);
    validate_map(game->map, 0);
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
    game->enemy_x = -1;
    game->enemy_y = -1;
    for (int y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            if (game->map[y][x] == 'C')
                game->collectibles++;
            else if (game->map[y][x] == 'X')
            {
                game->enemy_x = x;
                game->enemy_y = y;
            }
        }
    }
    init_player_position(game);
    game->win = mlx_new_window(game->mlx, game->map_width * game->tile_size,
        game->map_height * game->tile_size, "So Long");
    if (!game->win)
        error_exit("Failed to create a game window.");
    load_textures(game);
    render_map(game);
    srand(time(NULL));

	if (game->enemy_x != -1 && game->enemy_y != -1)
		mlx_loop_hook(game->mlx, move_enemy, game);
	handle_events(game);
	mlx_loop(game->mlx);
}

void	load_textures(t_game *game)
{
	int	size;

	size = game->tile_size;
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &size, &size);
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &size, &size);
	game->collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &size, &size);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &size, &size);
	game->empty = mlx_xpm_file_to_image(game->mlx, "textures/empty.xpm", &size, &size);
	game->enemy = mlx_xpm_file_to_image(game->mlx, "textures/enemy.xpm", &size, &size);
	if (!game->enemy || !game->wall || !game->player || !game->collectible || !game->exit || !game->empty)
		error_exit("Failed to load textures.");
}

int	close_game(t_game *game)
{
	free_map(game->map);
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
}

void move_player(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= game->map_width || 
        new_y < 0 || new_y >= game->map_height)
        return;
    if (game->map[new_y][new_x] == '1')
        return;
    if (game->map[new_y][new_x] == 'C')
        game->collectibles--;
    if (game->map[new_y][new_x] == 'E')
    {
        if (game->collectibles == 0)
        {
            printf("Congratulations! You won by collecting all items!\n");
            close_game(game);
            return;
        }
        else
            return;
    }
	if (new_x == game->enemy_x && new_y == game->enemy_y)
    {
        printf("Game Over! Enemy caught you.\n");
        close_game(game);
        return;
    }
    game->map[game->player_y][game->player_x] = '0';
    game->player_x = new_x;
    game->player_y = new_y;
    game->map[new_y][new_x] = 'P';
    game->moves++;
    printf("Moves: %d\n", game->moves);
    render_map(game);
}


int handle_keypress(int keycode, t_game *game)
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

void init_player_position(t_game *game)
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
                return;
            }
			x++;
        }
		y++;
    }
    error_exit("Player position not found in map.");
}

void handle_events(t_game *game)
{
    mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
    mlx_hook(game->win, 17, 0L, close_game, game);
}

int move_enemy(void *param)
{
    t_game *game = (t_game *)param;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int random_dir = rand() % 30;
    int new_x = game->enemy_x + dx[random_dir];
    int new_y = game->enemy_y + dy[random_dir];
    if (new_x >= 0 && new_x < game->map_width && 
        new_y >= 0 && new_y < game->map_height && 
        game->map[new_y][new_x] != '1' &&
        game->map[new_y][new_x] != 'C')
    {
        if (new_x == game->player_x && new_y == game->player_y)
		{
            printf("Game Over! Enemy caught you.\n");
            close_game(game);
            return (0);
        }
        game->map[game->enemy_y][game->enemy_x] = '0';
        game->enemy_x = new_x;
        game->enemy_y = new_y;
        game->map[new_y][new_x] = 'X';
    }
    render_map(game);
    return (0);
}




