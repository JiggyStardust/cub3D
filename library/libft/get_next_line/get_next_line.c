/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:48:07 by hpirkola          #+#    #+#             */
/*   Updated: 2024/07/12 17:51:38 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char *static_buf)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	j = 0;
	if (!static_buf)
		return (NULL);
	if (!find_line_break(static_buf))
		return (free_the_buf(static_buf));
	while (static_buf[i] != '\n')
		i++;
	if (static_buf[i + 1] == '\0')
		return (free_the_buf(static_buf));
	next_line = malloc((ft_strlen(static_buf) - i + 1) * sizeof(char));
	if (!next_line)
		return (free_the_buf(static_buf));
	i++;
	while (static_buf[i])
		next_line[j++] = static_buf[i++];
	next_line[j] = '\0';
	free(static_buf);
	return (next_line);
}

char	*copy_line(char *static_buf)
{
	char	*line;
	int		i;

	i = 0;
	if (static_buf == NULL)
		return (NULL);
	line = allocate_line(static_buf);
	if (!line)
		return (NULL);
	i = 0;
	while (static_buf[i])
	{
		if (static_buf[i] == '\n')
		{
			line[i] = static_buf[i];
			i++;
			break ;
		}
		line[i] = static_buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	find_line_break(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_file(int fd, char *static_buf)
{
	char	buffer[BUFFER_SIZE + 1];
	int		size;

	size = 1;
	if (static_buf == NULL)
	{
		static_buf = malloc(1 * sizeof(char));
		if (!static_buf)
			return (NULL);
		static_buf[0] = 0;
	}
	while (size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size < 0)
			return (free_the_buf(static_buf));
		buffer[size] = '\0';
		static_buf = join(static_buf, buffer);
		if (!static_buf)
			return (NULL);
		if (find_line_break(buffer))
			break ;
	}
	return (static_buf);
}

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (static_buf != NULL)
		{
			free(static_buf);
			static_buf = NULL;
		}
		return (NULL);
	}
	if (!find_line_break(static_buf))
		static_buf = read_file(fd, static_buf);
	if (static_buf == NULL)
		return (NULL);
	line = copy_line(static_buf);
	if (!line)
	{
		free(static_buf);
		static_buf = NULL;
		return (NULL);
	}
	static_buf = next_line(static_buf);
	return (line);
}
