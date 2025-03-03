#include "../cub3d.h"

char	*create_mapstr(int fd)
{
	char	*map;
	char	*line;
	char	*temp;

	map = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		temp = map;
		map = ft_strjoin(map, line);
		free(line);
		free(temp);
		if (!map)
		{
			ft_printf("Error\ncreate_map() ft_strjoin\n");
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (map);
}

char	**create_map(char *path)
{
	int		fd;
	char	*map_line;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nThere's no such /map/path my lady.\n");
		return (0);
	}
	map_line = create_mapstr(fd);
	if (!map_line)
		return (NULL);
	map = ft_split(map_line, '\n');
	free(map_line);
	close(fd);
	return (map);
}
