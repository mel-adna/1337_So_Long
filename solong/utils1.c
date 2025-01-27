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

int close_game(t_game *game)
{
    if (game->wall)
        mlx_destroy_image(game->mlx, game->wall);
    if (game->player)
        mlx_destroy_image(game->mlx, game->player);
    if (game->collectible)
        mlx_destroy_image(game->mlx, game->collectible);
    if (game->exit)
        mlx_destroy_image(game->mlx, game->exit);
    if (game->empty)
        mlx_destroy_image(game->mlx, game->empty);
    if (game->enemy)
        mlx_destroy_image(game->mlx, game->enemy);
    if (game->map)
        free_map(game->map);
    if (game->win)
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
    {
        game->collectibles--;
        printf("\nCollectible gathered! Remaining: %d\n", game->collectibles);
    }
    
    if (game->map[new_y][new_x] == 'E')
    {
        if (game->collectibles == 0)
        {
            printf("\nCongratulations! You won!\n");
            printf("Final Score: %d moves\n", game->moves + 1);
            close_game(game);
            return;
        }
        else
        {
            printf("\nCollect all items first! Remaining: %d\n", game->collectibles);
            return;
        }
    }

    if (new_x == game->enemy_x && new_y == game->enemy_y)
    {
        printf("\nGame Over! You ran into the enemy!\n");
        printf("Final Score: %d moves, %d collectibles remaining\n", 
              game->moves, game->collectibles);
        close_game(game);
        return;
    }
    game->map[game->player_y][game->player_x] = '0';
    game->player_x = new_x;
    game->player_y = new_y;
    game->map[new_y][new_x] = 'P';
    game->moves++;
    
    printf("\rMoves: %d", game->moves);
    fflush(stdout);
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
    static int delay = 0;
    static char last_pos = '0';
    static int direction = 0;
    static int steps = 0;

    if (++delay < 2000)
        return (0);
    delay = 0;
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    if (steps++ > 3)
    {
        direction = (direction + 3) % 4;
        steps = 0;
    }
    int new_x = game->enemy_x + dx[direction];
    int new_y = game->enemy_y + dy[direction];
    if (new_x < 0 || new_x >= game->map_width || 
        new_y < 0 || new_y >= game->map_height || 
        game->map[new_y][new_x] == '1' ||
        game->map[new_y][new_x] == 'E')
    {
        for (int i = 0; i < 4; i++)
        {
            direction = (direction + 1) % 4;
            new_x = game->enemy_x + dx[direction];
            new_y = game->enemy_y + dy[direction];
            
            if (new_x >= 0 && new_x < game->map_width && 
                new_y >= 0 && new_y < game->map_height && 
                game->map[new_y][new_x] != '1' &&
                game->map[new_y][new_x] != 'E')
                break;
        }
    }
    if (abs(game->player_x + game->enemy_x) + abs(game->player_y - game->enemy_y) < 6)
    {
        new_x = game->enemy_x + (game->player_x > game->enemy_x ? 1 : -1);
        new_y = game->enemy_y + (game->player_y > game->enemy_y ? 1 : -1);
        steps = 0;
    }
    if (new_x >= 0 && new_x < game->map_width && 
        new_y >= 0 && new_y < game->map_height && 
        game->map[new_y][new_x] != '1' &&
        game->map[new_y][new_x] != 'E')
    {
        if (game->enemy_x == game->player_x && game->enemy_y == game->player_y)
        {
            printf("\nGame Over! Enemy caught you!\n");
            printf("Final Score: %d moves, %d collectibles remaining\n", 
                  game->moves, game->collectibles);
            close_game(game);
            return (0);
        }
        char current_pos = game->map[new_y][new_x];
        game->map[game->enemy_y][game->enemy_x] = last_pos;
        game->enemy_x = new_x;
        game->enemy_y = new_y;
        last_pos = current_pos;
        game->map[new_y][new_x] = 'X';
        render_map(game);
    }
    else
    {
        direction = (direction + 2) % 4;
        steps = 0;
    }
    return (0);
}




