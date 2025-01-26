#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "gnl/get_next_line_bonus.h"
# include "libft/libft.h"

typedef struct s_game
{
    char    **map;
}   t_game;


char    **read_map(const char *file_path);
void	validate_map(char **map, int i);
void    validate_components(char **map);
int     is_all_walls(const char *line);
void    error_exit(const char *message);
void    free_map(char **map);

#endif
