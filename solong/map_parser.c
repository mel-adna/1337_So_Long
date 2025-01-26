#include "so_long.h"

char *read_and_concat_file(int fd)
{
    char *line;
    char *temp_map = NULL;
    char *temp;

    while ((line = get_next_line(fd)))
    {
        if (!temp_map)
            temp_map = ft_strdup(line);
        else
        {
            temp = temp_map;
            temp_map = ft_strjoin(temp_map, line);
            free(temp);
        }
        free(line);
    }
    return temp_map;
}

char **read_map(const char *file_path)
{
    int fd;
    char *temp_map;
    char **map;

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open the map file.");

    temp_map = read_and_concat_file(fd);
    close(fd);
	if (!temp_map)
        error_exit("Map is empty.");
    map = ft_split(temp_map, '\n');
    free(temp_map);
    return map;
}
