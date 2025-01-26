#include "so_long.h"

char	**read_map(const char *file_path)
{
	int		fd;
	char	*line;
	char	**map;
	char	*temp_map;
	char	*temp;

	temp_map = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open the map file.");
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
	close(fd);
	if (!temp_map)
		error_exit("Map is empty.");
	map = ft_split(temp_map, '\n');
	return (free(temp_map), map);
}
